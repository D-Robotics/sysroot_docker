��    �      t  �   �
      `     a     o     �     �  k   �               $     *  �  0  5  �      1        E  1   X     �     �     �     �     �     �     �     �               )     6     O     h     q     ~     �     �     �  "   �     �     �     �          &     9     R     `     r     �     �     �     �  
   �     �  ,   �          '  	   E     O     _     x     �     �  0   �     �     �     �       	        )  =   9     w     �  	   �  
   �     �     �     �     �          "  	   A     K     c     �     �     �  1   �     
     &     ?  0   \     �  !   �     �     �  O         P     \  
   j     u  "   �     �     �  	   �     �  	   �               -     B     Z  .   y  	   �     �  
   �     �  )   �     �          !     8      L     m     ~     �  !   �     �  ?   �  
        *     ;     C     S     c     s  A   �  (   �     �  #      !   5   *   W   B   �      �      �   7   �      !!  !   9!  .   [!     �!  "   �!     �!     �!     �!     �!     �!     "     *"     ;"     T"      m"  *   �"  !   �"  )   �"  #   #     )#  �   D#     9$     ?$  A   G$  !   �$     �$     �$     �$  �  �$     �&     �&     �&     �&  r   �&     b'     k'     p'     v'  �  |'  .  Y)  *  �+  M   �-     .  B   .     X.     s.     .     �.     �.     �.  
   �.     �.     �.     �.     /     /     ,/  
   F/     Q/     d/     }/     �/     �/  +   �/     �/     �/     �/     0     )0     =0     W0     j0  	   �0     �0     �0     �0  
   �0     �0     �0  $   �0      1  !   ,1     N1     [1     p1     �1     �1     �1  0   �1     �1     2     2     '2     52     A2  R   Q2     �2     �2  	   �2  
   �2     �2     �2     3     3     33     O3     k3     r3  $   3     �3     �3     �3  *   �3     4     +4     ?4  *   V4     �4     �4     �4     �4  c   �4     <5     I5     V5     b5  .   n5     �5     �5     �5     �5     �5     6     6     (6      66  $   W6  :   |6     �6     �6     �6     �6  )    7     *7     ?7     S7     l7     }7     �7     �7     �7  #   �7     �7  3   8  
   ;8     F8     W8     ^8     n8     |8     �8  A   �8  '   �8     9  "   (9      K9  %   l9  J   �9     �9     �9  M   :     T:     g:  *   ~:     �:     �:     �:  
   �:     �:     �:     ;     *;     <;     I;     _;     r;     �;      �;  &   �;  "   �;     <  �   +<     &=     -=  R   4=     �=     �=     �=     �=     O           3   �   �   H       �   �   Z      \       �              ^   Q   q   R   �       >      p       %             '   8   E   K   �                                �          t   /       `   �   �      ]       .   A   �   v       
      +                  �             :   o       n   �   �       *   �   J   G   �       s   	   2   M   �   T   �   j       h   )   �   [       6   l   �   0   W   �   �   �   N          #      y   �                  z   !   ;   u   �   (           <               c   -   4      I   ,   �   d   }   �   �   B           9   �      w   S   �      Y           $           �   P           e   �   �   &       i      �   a   X   �   �   1      _   =   |   m           �          �   r   U   �   �   �      g   5   L   b   @      ?   D   �   f              V   "   ~   �                 7   C           {   k   x                  �   F            	%ld absolute 	%ld absolute not-standard 	%ld not-standard 	(same route) 
  -s <source>   source ip address
  <destination> dns name or ip address

For more details see arping(8).
 
%cSRR:  
NOP 
RR:  
TS:  
Usage
  tracepath [options] <destination>

Options:
  -4             use IPv4
  -6             use IPv6
  -b             print both name and ip
  -l <length>    use packet <length>
  -m <hops>      use maximum <hops>
  -n             no dns name resolution
  -p <port>      use destination <port>
  -V             print version and exit
  <destination>  dns name or ip address

For more details see tracepath(8).
 
Usage:
  arping [options] <destination>

Options:
  -f            quit on first reply
  -q            be quiet
  -b            keep on broadcasting, do not unicast
  -D            duplicate address detection mode
  -U            unsolicited ARP mode, update your neighbours
  -A            ARP answer mode, update your neighbours
  -V            print version and exit
  -c <count>    how many packets to send
  -w <timeout>  how long to wait for a reply
  -i <interval> set interval between packets (default: 1 second)
  -I <device>   which ethernet device to use 
Usage:
  clockdiff [options] <destination>

Options:
                without -o, use icmp timestamp only (see RFC0792, page 16)
  -o            use ip timestamp and icmp echo
  -o1           use three-term ip timestamp and icmp echo
  -T, --time-format <ctime|iso>
                  specify display time format, ctime is the default
  -I            alias of --time-format=iso
  -h, --help    display this help
  -V, --version print version and exit
  <destination> dns name or ip address

For more details see clockdiff(8).
 
host=%s rtt=%ld(%ld)ms/%ldms delta=%dms/%dms %s
 
unknown option %x 
wrong data byte #%zu should be 0x%x but was 0x%x      Resume: pmtu %d     %1x %04x   %02x  %02x %04x  %1x  %1x  %02x %04x %04x  %ld.%03ldms
  (BAD CHECKSUM!)  (DUP!)  (truncated)  (truncated)
  UNSOLICITED?
  icmp_seq=%u  parse error (too short)  parse error (truncated)  refused  time=%ld ms  time=%ld.%01ld ms  time=%ld.%02ld ms  time=%ld.%03ld ms  ttl=%d  unexpected error in inet_ntop(%s)  unknown  unknown code(%02x)  unknown qtype(0x%02x) %2d:  no reply
 %2d:  send failed
 %2d?: reply received 8)
 %3ld.%03ldms  %d bytes from %s: %d request(s) %ld packets transmitted,  %ld received %ld/%ld packets, %d%% loss %s from  %s is down %s is unreachable %s time transmitted in a non-standard format %s%d broadcast(s) %sipg/ewma %d.%03d/%d.%03d ms %spipe %d %zu data bytes
 %zu(%zu) bytes of data.
 (BAD CHECKSUM) (BAD CHECKSUM)
 (New nexthop: %s)
 (This broken router returned corrupted payload)  , %g%% packet loss , +%ld corrupted , +%ld duplicates , +%ld errors , code=%d , flow 0x%05x,  , min/avg/ewma/max = %ld.%03ld/%lu.%03ld/%d.%03d/%ld.%03ld ms , time %ldms --- %s ping statistics ---
 ; seq=%u; ARPING %s  Address Mask Reply
 Address Mask Request
 Address unreachable Administratively prohibited Bad ICMP type: %d
 Beyond scope of source address Broadcast Defragmentation failure Dest Unreachable, Bad Code: %d
 Destination Host Prohibited
 Destination Host Unknown
 Destination Host Unreachable
 Destination Host Unreachable for Type of Service
 Destination Net Prohibited
 Destination Net Unknown
 Destination Net Unreachable
 Destination Net Unreachable for Type of Service
 Destination Port Unreachable
 Destination Protocol Unreachable
 Destination unreachable:  Device %s not available. Do you want to ping broadcast? Then -b. If not, check your local firewall rules Echo Reply
 Echo Request
 Echo reply Echo request Frag needed and DF set (mtu = %u)
 Frag reassembly time exceeded
 From %s icmp_seq=%u  From %s:  From %s: icmp_seq=%u  Hop limit IDN encoding error: %s Information Reply
 Information Request
 Interface "%s" is down
 Interface "%s" is not ARPable
 Interface "%s" is not ARPable (no ll address)
 MLD Query MLD Reduction MLD Report No route Only one -4 or -6 option may be specified Overflow %d hops
 Packet filtered
 Packet too big: mtu=%u Parameter problem:  Parameter problem: pointer = %u
 Port unreachable Qtype conflict
 Received %d response(s) Sent %d probes (%d broadcast(s))
 Subject type conflict
 Suitable device could not be determined. Please, use option -I. Timestamp
 Timestamp Reply
 Unicast Unknown code %d Unknown header  Unknown option  Unrecorded hops: %d
 Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst Data
 WARNING: failed to install socket filter WARNING: interface is ignored WARNING: pinging broadcast address
 WARNING: setsockopt(SO_DONTROUTE) WARNING: using default broadcast address.
 Warning: source address might be selected on device other than: %s Wrong timestamp %d
 cannot copy: %s cannot flood; minimal interval allowed for user is %dms cannot set broadcasting cannot set multicast time-to-live cannot set preload to value greater than 3: %d cannot set unicast time-to-live dn_comp() returned too long result for  for %s  from %s %s
 from %s %s:  inappropriate subject name: %s invalid -M argument: %s invalid argument measure: unknown failure memory allocation failed multicast ping does not fragment multicast ping with too short interval: %d no source address in not-DAD mode only one -4 or -6 option may be specified packet too short (%d bytes) from %s packet too short: %d bytes ping -6 -N <nodeinfo opt>
Help:
  help
Query:
  name
  ipv6
  ipv6-all
  ipv6-compatible
  ipv6-global
  ipv6-linklocal
  ipv6-sitelocal
  ipv4
  ipv4-all
Subject:
  subject-ipv6=addr
  subject-ipv4=addr
  subject-name=name
  subject-fqdn=name
 reply request rtt min/avg/max/mdev = %ld.%03ld/%lu.%03ld/%ld.%03ld/%ld.%03ld ms scope discrepancy among the nodes too long scope name unknown iface: %s wrong timestamps
 Project-Id-Version: iputils
Report-Msgid-Bugs-To: 
PO-Revision-Date: 2022-02-05 12:39+0000
Last-Translator: Chuhao Li <Unknown>
Language-Team: Chinese (Simplified) <https://translate.fedoraproject.org/projects/iputils/iputils/zh_CN/>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Launchpad-Export-Date: 2024-02-12 12:42+0000
X-Generator: Launchpad (build 9643586c585856148a18782148972ae9c1179d06)
Language: zh_CN
 	%ld 绝对 	%ld 绝对非标准 	%ld 非标准 	(同一路由) 
  -s <source>   源 ip 地址
  <destination> dns 名称或者 ip 地址

了解更多信息请参阅 arping(8).
 
%cSRR:  
NOP 
RR:  
TS:  
用法
  tracepath [options] <destination>

可用的选项:
  -4             使用 IPv4
  -6             使用 IPv6
  -b             同时显示名称和 ip
  -l <length>    指定包长度为 <length>
  -m <hops>     指定最大跃点数为 <hops>
  -n             不进行名称解析
  -p <port>      目标端口号 <port>
  -V             显示版本信息并退出
  <destination>  目标主机 dns 名称或 ip 地址

了解更多信息请参阅 tracepath(8).
 
Usage:
  arping [options] <destination>

Options:
  -f             收到回复就退出
  -q            不要打印信息
  -b            始终使用广播而不是单拨
  -D            重复地址检测模式
  -U           主动 ARP 模式, 更新邻居 ARP 表
  -A            ARP 应答模式, 更新邻居 ARP 表
  -V            显示版本号然后退出
  -c <count>    指定发送多少个包
  -w <timeout>  指定等待超时时间
  -i <interval> 设置两个包之间的间隔时间 (默认: 1 秒)
  -I <device>   指定使用的设备 
Usage:
  clockdiff [options] <destination>

Options:
                如不指定 -o，则仅使用 ICMP 时间缀 (参阅 RFC0792，第 16 页)
  -o            使用 ip 时间缀和 ICMP 回复
  -o1           使用 3-term ip 时间缀和 ICMP 回复
  -T, --time-format <ctime|iso>
                  指定时间显示格式，默认是 ctime
  -I            --time-format=iso 的别名
  -h, --help    显示这个帮助
  -V, --version 显示版本信息并退出
  <destination> dns 名称或 ip 地址

需要更多信息请查看 clockdiff(8).
 
主机=%s 来回延迟=%ld(%ld)毫秒/%ld毫秒 相差=%d毫秒/%d毫秒 %s
 
未知选项： %x 
错误的数据字节 #%zu 预期为 0x%x 但实际接收到 0x%x      回程: 路径MTU %d     %1x %04x   %02x  %02x %04x  %1x  %1x  %02x %04x %04x  %ld.%03ld毫秒
  (CHECKSUM 错误)  (重复!)  (已截断)  (已截断)
  不请自来？
  icmp_seq=%u  解析错误 (太短)  解析错误 (被截断)  被拒绝  时间=%ld 毫秒  时间=%ld.%01ld 毫秒  时间=%ld.%02ld 毫秒  时间=%ld.%03ld 毫秒  ttl=%d  在 inet_ntop(%s) 发生未预期的错误  未知  未知代码(%02x)  未知的 qtype(0x%02x) %2d:  无应答
 %2d:  发送失败
 %2d?: 回复已接收 8)
 %3ld.%03ld 毫秒  %d 字节，来自 %s: %d 请求 已发送 %ld 个包，  已接收 %ld 个包 %ld/%ld 个包，%d%% 丢失 %s 来自  %s 已关闭 %s 不可达 %s 以非标准格式传输的时间 %s%d 广播 %sipg/ewma %d.%03d/%d.%03d 毫秒 %s 管道 %d %zu 字节的数据
 %zu(%zu) 字节的数据。
 (CHECKSUM 错误) (CHECKSUM 错误)
 (新的下一跳: %s)
 (这条损坏的路由返回了错误的数据)  , %g%% 包丢失 , +%ld 损坏 , +%ld 重复 , +%ld 错误 , 代码=%d , flow 0x%05x,  , 最小/平均/移动平均/最大 = %ld.%03ld/%lu.%03ld/%d.%03d/%ld.%03ld 毫秒 , 耗时 %ld 毫秒 --- %s ping 统计 ---
 ; seq=%u; ARPING %s  地址掩码应答
 地址掩码请求
 地址不可达 已被管理员禁止 错误的 ICMP 类型：%d
 超出源的地址范围外 广播 分段失败 目标不可达，错误代码：%d
 目标主机被禁止
 目标主机未知
 目标主机不可达
 对于此 ToS 而言目标主机不可达
 目标网络被禁止。
 目标网络未知
 目标网络不可达
 对于此 ToS 而言目标网络不可达
 目标端口不可达
 目标协议不可达
 目标不可达：  设备 %s 不可用. 您想要 ping 广播地址吗？若是则加上参数 -b，否则检查你的本地防火墙规则 Echo 应答
 Echo 请求
 Echo 应答 Echo 请求 需要分段但是设置了 DF （mtu = %u）
 分段重建时间超时
 来自 %s icmp_seq=%u  来自%s ：  来自 %s: icmp_seq=%u  跃点数上限 IDN 编码错误：%s 应答信息
 信息请求
 网络接口 “%s” 已停止
 网络接口 “%s” 不适用 ARP
 网络接口 “%s” 不适用 ARP（没有 ll 地址）
 组播组查询 组播组退出 组播组报告 没有路由（可达） 只能使用参数 -4 或 -6 中的一个 超过 %d 跃点数
 数据包被过滤
 数据包太大：MTU=%u 参数问题：  参数问题：指针=%u
 端口不可达 Qtype 冲突
 已接受到 %d 个响应 发送 %d 次探测 (%d 次广播)
 主题类型冲突
 无法确定合适的设备。请使用选项 -I。 时间戳
 时间戳回复
 单播 未知代码 %d 未知头部  未知选项  未记录的跃点数: %d
 Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst Data
 警告：无法安装套接字过滤器 警告：接口被忽略 警告：正在 ping 广播地址
 警告：setockopt(SO_DONTROUTE) 警告：使用默认广播地址。
 警告：可能在除以下设备之外的设备上选择了源地址：%s 错误的时间戳 %d
 无法打开：%s 不能 ping flood，对于用户而言最小的 ping 间隔时间是 %d毫秒 不能设置广播 不能设置多播 TTL 不能将 preload 设置到 3 以上的 %d 不能设置单拨的 TTL dn_comp() 的返回太长 对于  对于 %s  来自 %s %s
 来自 %s %s  不恰当的主题名称：%s 无效参数：%s 无效参数 措施：未知故障 内存分配错误 多播 ping 不分片 间隔太短的多播 ping：%d 非 DAD 模式下没有源地址 只接受参数 -4 或 -6 中的一个 过短的包 (%d 字节) 来自 %s 过短的包: %d 字节 ping -6 -N <节点信息选项>
Help:
  help
Query:
  name
  ipv6
  ipv6-all
  ipv6-compatible
  ipv6-global
  ipv6-linklocal
  ipv6-sitelocal
  ipv4
  ipv4-all
Subject:
  subject-ipv6=addr
  subject-ipv4=addr
  subject-name=name
  subject-fqdn=name
 回复 请求 rtt 最小/平均/移动平均/最大 = %ld.%03ld/%lu.%03ld/%ld.%03ld/%ld.%03ld ms 节点之间的范围差异 作用域名称太长 未知界面：%s 错误的时间戳
 