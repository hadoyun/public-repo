# encoding!!

## ANSI
ANSI: 협회 이름 (**A**merican **N**ational **S**tandards **I**nstitute, 미국 국가표준 협회)

## ASCII (American Standard Code for Information Interchange)
ASCII: 협회에서 제시한 (미국용) 표준 코드 체계
7 bit ( 경우의 수 2^7, 범위 [0, 127] )이기 때문에, 윈도우즈(운영체제)에서는 코드 페이지로 확장해서 사용한다.

```

65 == A 
가정 -  65 65 == HA라면?

65 65 는 뭘까요...?

```
## Microsoft의 코드 페이지 (Code Page, CP)
41392 ==  0xA1B0 == (리틀 엔디언) B0 A1 == '가' 
그렇다면? 0xA1B0은 항상 가 일까..?

답은 아니다!
한국어 윈도우즈 (CP949)에서 '가'라고 쓴 텍스트 파일을 ANSI 인코딩으로 저장한 후
일본어 윈도우즈를 쓰는 친구에게 보내면 '가'라고 나오지 않고 깨져서 나온다..!!

**때문에 등장한 것이 바로 유니코드!이다.**
(유니코드는 한 문자가 한 숫자와 대입 되기 때문에! 어디 나라에서든 해당 숫자는 해당 문자를 나타낸다. 즉 깨지는 현상이 없다!)


문제로 돌아와보자!~
```cpp
OutputDebugStringA(); // 난 char를 사용해
OutputDebugStringW(); // 난 wchar_t를 받아!
```
는 무엇이 다를까?

-A는 ANSI를 의미하고
-W는 Wide, 즉 유니코드를 의미한다.

이때 wchar_t 자료형은 윈도우즈에서는 2바이트이다. (wchar_t가 몇 바이트인지는 운영체제마다 다르다!)
따라서! 윈도우즈가 말하는 유니코드는 UTF-16일 것이다?
그렇다! => https://docs.microsoft.com/en-us/windows/win32/learnwin32/working-with-strings 확인

