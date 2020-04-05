<html> 
  <head>
  
  <title>레브랜드</title> 
  
  <!-- java script --> 
  <script language="JavaScript" type="text/javascript" SRC="../javascript/list.js"></script>
  <script language="JavaScript"> 
  <!-- 
  
  // 입력폼값 체크 함수 
  function SubmitForm() 
  { 
      var id = document.form.elements["id"].value; 
      var name = document.form.elements["name"].value;
      var pwd = document.form.elements["pwd"].value; 
      var pwd2 = document.form.elements["pwd2"].value; 
      var email = document.form.elements["email"].value; 
      var phone = document.form.elements["phone"].value;  
      
      // 아이디 체크 
      if(id.length < 3 || id.length > 15) 
      { 
          alert("3자이상 15자 이하의 아이디를 입력하세요."); 
          document.form.id.focus(); 
          return false; 
      } 
      else 
      { 
          // 아이디의 유효성 체크 
          if(!CheckStr(id) ||  id.indexOf(" ") != -1) 
          { 
              alert("ID는 공백 없이 영문자나 숫자만 입력 하실수 있습니다!"); 
              document.form.id.focus(); 
              return false; 
          } 
      } 
      
      // 비밀번호 체크 
      if(pwd.length < 4 || pwd.length > 15) 
      { 
          alert("4자이상 15자 이하의 비밀번호를 입력하세요."); 
          document.form.pwd.focus(); 
          return false; 
      } 
      else 
      { 
          // 비밀번호의 유효성 체크 
          if(!CheckStr(pwd) ||  pwd.indexOf(" ") != -1) 
          { 
              alert("비밀번호는 공백 없이 영문자나 숫자만 입력 하실수 있습니다!"); 
              document.form.pwd.focus(); 
              return false; 
          } 
          else { 
              if(pwd != pwd2) { 
              alert("비밀번호와 비번확인이 일치하지 않습니다."); 
              document.form.pwd2.focus(); 
              return false; 
              } 
          } 
      } 
  
      // 이름 체크 
      if(name.length < 1 || name.indexOf(" ") != -1) 
      { 
         alert("이름을 공백없이 입력하시오."); 
         document.form.name.focus(); 
         return false; 
      } 
      
      // 이메일 체크
      if( CheckStr(email, " ", "") != 0 ) 
			{
			  if( check_email(email) == 0 )
			  {
			    alert("이메일을 다시 입력해 주세요");      
			    document.form.email.focus();
			    return false;
			  }
			}  

     document.form.action ="./login_insert.asp"
     document.form.submit();
  }
  
  // --> 
  </script> 
  
  <link rel="stylesheet" href="../stylesheet/style.css">
  
  </head> 

  <body onload="document.form.id.focus();"> 
  <h3>레브랜드 멤버 등록</h3>
  아이디, 비밀번호, 이름만 입력하셔도 됩니다<br>
  <br>
  <form method=post name=form>
    <table border=0 witdh=100% cellpadding=3 cellspacing=1> 
      <tr>
        <td align=right bgcolor=#eeeeee>아이디</td> 
        <td> <input type=text size=15 name=id></td>
      </tr> 
      <tr>
        <td align=right bgcolor=#eeeeee>비밀번호</td> 
        <td> <input type=password size=15 name=pwd></td>
      </tr> 
      <tr>
        <td align=right bgcolor=#eeeeee>비번확인</td> 
        <td> <input type=password size=15 name=pwd2></td>
      </tr> 
      <tr>
        <td align=right bgcolor=#eeeeee>이름</td> 
        <td> <input type=text size=15 name=name></td>
      </tr>
      <tr>
        <td align=right bgcolor=#eeeeee>이메일</td> 
        <td> <input type=text size=15 name=email></td>
      </tr> 
      <tr>
        <td align=right bgcolor=#eeeeee>연락처</td> 
        <td> <input type=text size=15 name=phone></td>
      </tr>              
      <tr>
        <td align=right colspan=2> 
          <img src=./images/join.gif style="border:0" alt="등록" onfocus='this.blur()'  onClick="SubmitForm();" > 
        </td>
      </tr>
    </table> 
  </form> 
  </body> 
</html>