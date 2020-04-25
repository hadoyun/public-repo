# encoding

ANSI - 협회 이름

ASCII - 협회에서 제시한 표준 코드 체계
2^7이기 때문에, 윈도우에서는 코드 페이지로 확장


```

65 == A 
가정 -  65 65 == HA라면?

65 65 는 뭘까요...?

```
CP - 코드 페이지

16진수 한자리가 1 바이트 이기 때문에 신경쓰지 않아도 된다.


41392 ==  0xA1B0 == (리틀 엔디언) B0 A1 == '가' 
그렇다면? 0xA1B0은 항상 가 일까..?

답은 아니다! (일본어 윈도우 쓰는 친구에게 가라고 쓰여진 ANSI를 보내면 깨져서 나온다..!)

**때문에 등장한 것이 바로 유니코드!이다.**
(유니코드는 한 문자가 한 숫자와 대입 되기 때문에! 일본어 윈도우를 써도 깨지지 않는다.)


문제로 돌아와보자!~
```cpp
OutputDebugStringA();
OutputDebugStringW(); // 난 wchar_t를 받아!
```
는 무엇이 다를까?

wchar_t == 윈도우즈에서는 2바이트 
따라서,! 즉 윈도우즈는 UTP - 16으로 인코딩을 한다!