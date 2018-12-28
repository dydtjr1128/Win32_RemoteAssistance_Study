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
