/*
 * Copyright 2026 D-Robotics Co., Ltd.
 *
 * Fast-path CAN API for FlexCAN shared-memory channels.
 *
 * This header provides a safe, opaque-handle wrapper over the FlexCAN
 * shared-memory (shm) TX/RX ring buffers exposed by the kernel driver via
 * /dev/flexcan_shm_tx_<ifname> and /dev/flexcan_shm_rx_<ifname>.
 *
 * All volatile pointer arithmetic and memory-barrier operations are hidden
 * inside the library.  Callers only need to:
 *   1. Open a TX and/or RX handle with canFastTxOpen() / canFastRxOpen().
 *   2. Send frames with canFastSend().
 *   3. Receive frames with canFastPollRx() + canFastRecv().
 *   4. Close handles with canFastTxClose() / canFastRxClose().
 *
 * The API is plain C so it can be consumed from both C and C++ code.
 */

#ifndef INCLUDE_CANHAL_HOBOT_CAN_HAL_FAST_H_
#define INCLUDE_CANHAL_HOBOT_CAN_HAL_FAST_H_

#include <stdint.h>
#include <stdlib.h>   /* strtoul — used by canFastParseId() */
#include <hobot_can_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------------
 * CAN ID masks (used for constructing / inspecting raw IDs)
 * -------------------------------------------------------------------------- */
#define CANFAST_EFF_MASK 0x1FFFFFFFU  /**< Extended frame ID mask (29-bit)   */
#define CANFAST_SFF_MASK 0x000007FFU  /**< Standard frame ID mask (11-bit)   */

/** Maximum CAN FD payload length. */
#define CANFAST_DATA_MAX  64u

/* --------------------------------------------------------------------------
 * Frame type constants for canframe.can_type
 *
 * Encoding (two bits):
 *   bit 0 — 0 = Standard Frame Format (SFF, 11-bit ID)
 *            1 = Extended Frame Format (EFF, 29-bit ID)
 *   bit 1 — 0 = Classic CAN
 *            1 = CAN FD with Bit Rate Switch (BRS always enabled)
 *
 * Convenience macros CANFAST_IS_EFF() / CANFAST_IS_FD() test each bit.
 * -------------------------------------------------------------------------- */
#define CANFAST_TYPE_CAN        0u  /**< Classic CAN,    standard frame (SFF) */
#define CANFAST_TYPE_CAN_EFF    1u  /**< Classic CAN,    extended frame (EFF) */
#define CANFAST_TYPE_CANFD      2u  /**< CAN FD + BRS,   standard frame (SFF) */
#define CANFAST_TYPE_CANFD_EFF  3u  /**< CAN FD + BRS,   extended frame (EFF) */

/** Non-zero when @t selects an extended frame (29-bit ID). */
#define CANFAST_IS_EFF(t)  (((t) & 1u) != 0u)
/** Non-zero when @t selects a CAN FD frame (BRS always on). */
#define CANFAST_IS_FD(t)   (((t) & 2u) != 0u)

/* --------------------------------------------------------------------------
 * struct canframe - shared frame type for both normal and fast CAN paths.
 *
 * Defined in hobot_can_hal.h.  The fast path uses struct canframe directly:
 *   - count and can_channel are present but unused in the fast path (set to 0)
 *   - can_type uses CANFAST_TYPE_* values instead of the legacy cantype enum
 *
 * Memory layout (sizeof == 80 bytes):
 *   offset  0 : time_stamp  (8 bytes)
 *   offset  8 : canid       (4 bytes)
 *   offset 12 : count       (1 byte)
 *   offset 13 : can_type    (1 byte)
 *   offset 14 : can_channel (1 byte)
 *   offset 15 : len         (1 byte)
 *   offset 16 : data        (64 bytes)
 *
 * Field semantics in the fast path:
 *   @time_stamp:   Hardware RX timestamp in µs (RX only; ignored on TX).
 *   @canid:        Raw numeric CAN identifier — NO flag bits, always a plain
 *                  number.  SFF: 0x000..0x7FF; EFF: 0x00000000..0x1FFFFFFF.
 *                  Whether SFF or EFF is determined by @can_type, not the ID.
 *   @count:        Unused in the fast path.  Always 0.
 *   @can_type:     One of the CANFAST_TYPE_* constants.
 *                  Use CANFAST_IS_EFF() / CANFAST_IS_FD() to query the bits.
 *   @can_channel:  Unused in the fast path.  Always 0.
 *   @len:          Payload byte count (0..8 for CAN, 0..64 for CANFD).
 *   @data:         Payload bytes.
 * -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
 * CAN ID utility functions (static inline — no library linkage required)
 * -------------------------------------------------------------------------- */

/**
 * canFastMakeStdId() - mask @id to a valid 11-bit standard CAN ID.
 * @id: Raw identifier; values above 0x7FF are silently truncated.
 */
static inline uint32_t canFastMakeStdId(uint32_t id)
{
    return id & CANFAST_SFF_MASK;
}

/**
 * canFastMakeExtId() - mask @id to a valid 29-bit extended CAN ID.
 * @id: Raw identifier; values above 0x1FFFFFFF are silently truncated.
 *
 * Note: no EFF flag is set in the return value — @canid in canframe
 * is always a plain number.  Use CANFAST_TYPE_CAN_EFF / CANFAST_TYPE_CANFD_EFF
 * in @can_type to indicate that this is an extended frame.
 */
static inline uint32_t canFastMakeExtId(uint32_t id)
{
    return id & CANFAST_EFF_MASK;
}

/**
 * canFastParseId() - parse a CAN ID string into a raw numeric ID.
 * @s: Decimal or hexadecimal string, e.g. "0x123", "291", "0x1FFFFFFF".
 *
 * Returns the plain numeric value, masked to 29 bits.  Store the result
 * in canframe.canid and set can_type appropriately.
 */
static inline uint32_t canFastParseId(const char *s)
{
    return (uint32_t)strtoul(s, NULL, 0) & CANFAST_EFF_MASK;
}

/**
 * canFastIsEff() - return non-zero if @can_type selects an extended frame.
 * @can_type: Value from canframe.can_type.
 */
static inline int canFastIsEff(uint8_t can_type)
{
    return CANFAST_IS_EFF(can_type) ? 1 : 0;
}

/**
 * canFastIsFd() - return non-zero if @can_type selects a CAN FD frame.
 * @can_type: Value from canframe.can_type.
 */
static inline int canFastIsFd(uint8_t can_type)
{
    return CANFAST_IS_FD(can_type) ? 1 : 0;
}

/* --------------------------------------------------------------------------
 * Opaque handles
 * -------------------------------------------------------------------------- */

/** Opaque TX channel handle returned by canFastTxOpen(). */
typedef struct canfast_tx_s canfast_tx_t;

/** Opaque RX channel handle returned by canFastRxOpen(). */
typedef struct canfast_rx_s canfast_rx_t;

/* --------------------------------------------------------------------------
 * TX API
 * -------------------------------------------------------------------------- */

/**
 * canFastTxOpen() - open the fast-path TX channel for a CAN interface.
 * @ifname: Interface name string, e.g. "can1".
 *          The library opens /dev/flexcan_shm_tx_<ifname> and maps the
 *          shared-memory TX ring buffer.
 *
 * Returns a non-NULL handle on success.  Returns NULL and prints a diagnostic
 * to stderr on failure (device not present, shm header invalid, etc.).
 *
 * The kernel module must have been loaded with shm_tx=1 for the device node
 * to exist.
 */
canfast_tx_t *canFastTxOpen(const char *ifname);

/**
 * canFastTxClose() - release all resources associated with a TX handle.
 * @tx: Handle returned by canFastTxOpen().  NULL is silently ignored.
 *      After this call @tx must not be used again.
 */
void canFastTxClose(canfast_tx_t *tx);

/**
 * canFastSend() - enqueue up to @count CAN/CANFD frames for transmission.
 * @tx:     Valid TX handle (must not be NULL).
 * @frames: Array of @count struct canframe to send.  The library copies the
 *          contents; the caller may reuse @frames immediately after the call.
 * @count:  Number of frames to enqueue (>= 1).
 *
 * For each frame, @can_type determines the bus format and frame format:
 *   CANFAST_TYPE_CAN       — classic CAN,  SFF (11-bit ID, len <= 8)
 *   CANFAST_TYPE_CAN_EFF   — classic CAN,  EFF (29-bit ID, len <= 8)
 *   CANFAST_TYPE_CANFD     — CAN FD + BRS, SFF (11-bit ID, len <= 64)
 *   CANFAST_TYPE_CANFD_EFF — CAN FD + BRS, EFF (29-bit ID, len <= 64)
 *
 * All frames are written into the ring first; a single release-store on
 * the head pointer then makes them all visible to the kernel.  One doorbell
 * write wakes the kernel for the entire batch, minimising per-frame overhead.
 *
 * Returns  > 0  number of frames actually enqueued (1..count).
 *              May be less than @count if the ring fills up mid-batch; the
 *              caller should check the return value and retry the remainder
 *              after canFastPollTx().
 *         -EAGAIN  if the TX ring is completely full (0 frames sent); call
 *                  canFastPollTx() and then retry.
 *         -EINVAL  if @tx or @frames is NULL, @count is 0, or the handle
 *                  is invalid.
 *         Other negative errno values on unexpected errors.
 *
 * Typical usage pattern (mirrors canFastRecv):
 *
 *   #define TX_BATCH 32
 *   struct canframe frames[TX_BATCH];
 *   // ... fill frames[], set can_type = CANFAST_TYPE_CANFD_EFF etc. ...
 *   int rc;
 *   do {
 *       rc = canFastSend(tx, frames, TX_BATCH);
 *       if (rc == -EAGAIN) canFastPollTx(tx, 10);
 *   } while (rc == -EAGAIN);
 */
int canFastSend(canfast_tx_t *tx, const struct canframe *frames,
                uint32_t count);

/**
 * canFastPollTx() - wait until the TX ring has space or the timeout expires.
 * @tx:         Valid TX handle.
 * @timeout_ms: Maximum wait time in milliseconds.  Pass 0 for a
 *              non-blocking check; pass -1 to wait indefinitely.
 *
 * Returns  1  if TX space is available (POLLOUT ready).
 *          0  on timeout.
 *         Negative errno on error.
 */
int canFastPollTx(canfast_tx_t *tx, int timeout_ms);

/* --------------------------------------------------------------------------
 * RX API
 * -------------------------------------------------------------------------- */

/**
 * canFastRxOpen() - open the fast-path RX channel for a CAN interface.
 * @ifname: Interface name string, e.g. "can1".
 *          The library opens /dev/flexcan_shm_rx_<ifname> and maps the
 *          shared-memory RX ring buffer.
 *
 * Returns a non-NULL handle on success, NULL on failure.
 *
 * The kernel module must have been loaded with shm_rx=1.
 */
canfast_rx_t *canFastRxOpen(const char *ifname);

/**
 * canFastRxClose() - release all resources associated with an RX handle.
 * @rx: Handle returned by canFastRxOpen().  NULL is silently ignored.
 */
void canFastRxClose(canfast_rx_t *rx);

/**
 * canFastRecv() - receive up to @max_count CAN/CANFD frames (non-blocking).
 * @rx:        Valid RX handle (must not be NULL).
 * @frames:    Caller-allocated array of at least @max_count struct canframe
 *             elements.  Filled with received frames on success.
 * @max_count: Maximum number of frames to dequeue in one call (>= 1).
 *
 * Drains up to @max_count frames from the ring in a single pass.  All
 * consumed slots are released to the kernel with one release-store after
 * the batch, minimising memory-barrier overhead compared with calling this
 * function once per frame.
 *
 * Each received frame has:
 *   .time_stamp   — hardware RX timestamp in µs
 *   .canid        — raw CAN ID, no flag bits
 *   .can_type     — CANFAST_TYPE_* reconstructed from kernel flags
 *   .len          — actual payload byte count
 *   .data[]       — payload
 *   .count / .can_channel — always 0
 *
 * Returns  > 0   number of frames written into @frames (1..max_count).
 *           0    ring was empty (no frames available).
 *          -EINVAL  @rx or @frames is NULL, @max_count is 0, or invalid handle.
 *
 * Typical usage pattern (mirrors canRecvMsgFrame):
 *
 *   #define BATCH 32
 *   struct canframe frames[BATCH];
 *
 *   int n = canFastPollRx(rx, 1000);   // wait up to 1 s
 *   if (n > 0) {
 *       int count = canFastRecv(rx, frames, BATCH);
 *       for (int i = 0; i < count; i++) {
 *           process(&frames[i]);
 *           // canFastIsEff(frames[i].can_type) → 1 if extended frame
 *           // canFastIsFd(frames[i].can_type)  → 1 if CANFD
 *       }
 *   }
 */
int canFastRecv(canfast_rx_t *rx, struct canframe *frames,
                uint32_t max_count);

/**
 * canFastPollRx() - wait until at least one RX frame is available.
 * @rx:         Valid RX handle.
 * @timeout_ms: Maximum wait time in milliseconds.  Pass 0 for a
 *              non-blocking check; pass -1 to wait indefinitely.
 *
 * Returns  1  if data is available (POLLIN ready).
 *          0  on timeout.
 *         Negative errno on error.
 */
int canFastPollRx(canfast_rx_t *rx, int timeout_ms);

/**
 * canFastRxDropped() - return the kernel's ring-overflow drop counter.
 * @rx: Valid RX handle.  Returns 0 if @rx is NULL or invalid.
 *
 * Each time the kernel fills the ring and cannot write a new frame it
 * increments this counter.  A non-zero value indicates the consumer is
 * too slow.
 */
uint32_t canFastRxDropped(canfast_rx_t *rx);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_CANHAL_HOBOT_CAN_HAL_FAST_H_ */
