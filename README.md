# Win32_Study
Win32_Study


## ToDo

<p>
  <ul>
    <li>- [x] Add screen capture</li>
    <li>- [x] Improve double buffering</li>    
    <li>- [ ] Add image compress(JPEG)</li>    
    <li>- [ ] Add network code(socket)</li>    
    <li>- [ ] Register service & make installer </li>    
  </ul>
</p>



## Error Log
<p>
  <ul>
    <li>
      서피스 프로 등 고해상도의 모니터에서 윈도우 DPI 스케일링으로 인해 GetSystemMetrics(SM_CXSCREEN)를 이용한 해상도 값 인식 시 문제 발생
       <ul>
         <li>
          SetProcessDPIAware() 를 이용하여 프로세스가 원래 스크린으로 인식하도록 함 그러나 MSDN에서는 API Call 보다는 Manifest 추가를 권장 ->               https://msdn.microsoft.com/ko-kr/C9488338-D863-45DF-B5CB-7ED9B869A5E2
         </li>
      </ul>
      <img src="https://user-images.githubusercontent.com/19161231/50512843-a391d280-0ad7-11e9-9a7d-ff3e3dbdd353.png">
    </li>    
  </ul>
</p>


## Dictionary

* `GetSystemMetrics(SM_CXSCREEN)` `GetSystemMetrics(SM_CYSCREEN)`

  * 스크린의 X 크기, Y크기를 리턴
 
* `GetWindowRect`

  * 윈도우의 현재 위치와 크기를 구해준다. (left, top)은 윈도우의 현재 좌상단 위치를 나타내는데 이 좌표는 전체 화면을 기준으로 한 좌표이다. (right, bottom)은 윈도우의 우하단 위치를 나타내며 역시 전체 화면을 기준으로 한 좌표이다. 윈도우의 현재 크기(폭과 높이)를 구하고 싶으면 right-left, bottom-top을 계산하면 된다.   
  * ```
    GetWindowRect(GetForegroundWindow(), &rt);// 활성중인 창 크기 가져올때 사용, 다른창 클릭하면 그 창 사이즈 
    GetWindowRect(hWnd, &rt);// 현재 창 사이즈 및 위치
    GetWindowRect(GetActiveWindow(), &rt);// 활성 창 정보
    ```

* `GetClientRect`

  * 윈도우의 작업영역 크기를 계산해 준다. 크기만 계산해 주기 때문에 좌상단(left, top)값은 항상 0,0이며 우하단 좌표(right, bottom)가 곧 윈도우의 크기를 나타낸다. 작업영역이란 윈도우의 타이틀바, 스크롤 바, 경계선, 메뉴 등을 제외한 영역이며 윈도우가 그리기를 하는 대상 영역이다

* `ScreenToClient`

  * 화면의 원점을 기준으로 하는 좌표 lpPoint를 hWnd의 작업 영역을 기준으로 하는 좌표로 변환한다. hWnd윈도우의 작업 영역 원점의 화면 좌표가 cx, cy일 때 lpPoint는 lpPoint.x - cx, lpPoint - cy로 변환된다. GetCursorPos, MoveWindow, GetWindowRect 등과 같이 화면 좌표를 리턴하는 함수로부터 작업 영역의 좌표로 변환하고자 할 때 이 함수를 사용한다.
