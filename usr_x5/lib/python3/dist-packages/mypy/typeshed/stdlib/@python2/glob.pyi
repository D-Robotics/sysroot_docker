from typing import AnyStr, Iterator, List

def glob(pathname: AnyStr) -> List[AnyStr]: ...
def iglob(pathname: AnyStr) -> Iterator[AnyStr]: ...
def glob1(dirname: str | unicode, pattern: AnyStr) -> List[AnyStr]: ...
def glob0(dirname: str | unicode, basename: AnyStr) -> List[AnyStr]: ...
def has_magic(s: str | unicode) -> bool: ...  # undocumented