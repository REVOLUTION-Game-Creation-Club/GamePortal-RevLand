<html> 
  <head>
  
  <title>���귣��</title> 
  
  <!-- java script --> 
  <script language="JavaScript" type="text/javascript" SRC="../javascript/list.js"></script>
  <script language="JavaScript"> 
  <!-- 
  
  // �Է����� üũ �Լ� 
  function SubmitForm() 
  { 
      var id = document.form.elements["id"].value; 
      var name = document.form.elements["name"].value;
      var pwd = document.form.elements["pwd"].value; 
      var pwd2 = document.form.elements["pwd2"].value; 
      var email = document.form.elements["email"].value; 
      var phone = document.form.elements["phone"].value;  
      
      // ���̵� üũ 
      if(id.length < 3 || id.length > 15) 
      { 
          alert("3���̻� 15�� ������ ���̵� �Է��ϼ���."); 
          document.form.id.focus(); 
          return false; 
      } 
      else 
      { 
          // ���̵��� ��ȿ�� üũ 
          if(!CheckStr(id) ||  id.indexOf(" ") != -1) 
          { 
              alert("ID�� ���� ���� �����ڳ� ���ڸ� �Է� �ϽǼ� �ֽ��ϴ�!"); 
              document.form.id.focus(); 
              return false; 
          } 
      } 
      
      // ��й�ȣ üũ 
      if(pwd.length < 4 || pwd.length > 15) 
      { 
          alert("4���̻� 15�� ������ ��й�ȣ�� �Է��ϼ���."); 
          document.form.pwd.focus(); 
          return false; 
      } 
      else 
      { 
          // ��й�ȣ�� ��ȿ�� üũ 
          if(!CheckStr(pwd) ||  pwd.indexOf(" ") != -1) 
          { 
              alert("��й�ȣ�� ���� ���� �����ڳ� ���ڸ� �Է� �ϽǼ� �ֽ��ϴ�!"); 
              document.form.pwd.focus(); 
              return false; 
          } 
          else { 
              if(pwd != pwd2) { 
              alert("��й�ȣ�� ���Ȯ���� ��ġ���� �ʽ��ϴ�."); 
              document.form.pwd2.focus(); 
              return false; 
              } 
          } 
      } 
  
      // �̸� üũ 
      if(name.length < 1 || name.indexOf(" ") != -1) 
      { 
         alert("�̸��� ������� �Է��Ͻÿ�."); 
         document.form.name.focus(); 
         return false; 
      } 
      
      // �̸��� üũ
      if( CheckStr(email, " ", "") != 0 ) 
			{
			  if( check_email(email) == 0 )
			  {
			    alert("�̸����� �ٽ� �Է��� �ּ���");      
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
  <h3>���귣�� ��� ���</h3>
  ���̵�, ��й�ȣ, �̸��� �Է��ϼŵ� �˴ϴ�<br>
  <br>
  <form method=post name=form>
    <table border=0 witdh=100% cellpadding=3 cellspacing=1> 
      <tr>
        <td align=right bgcolor=#eeeeee>���̵�</td> 
        <td> <input type=text size=15 name=id></td>
      </tr> 
      <tr>
        <td align=right bgcolor=#eeeeee>��й�ȣ</td> 
        <td> <input type=password size=15 name=pwd></td>
      </tr> 
      <tr>
        <td align=right bgcolor=#eeeeee>���Ȯ��</td> 
        <td> <input type=password size=15 name=pwd2></td>
      </tr> 
      <tr>
        <td align=right bgcolor=#eeeeee>�̸�</td> 
        <td> <input type=text size=15 name=name></td>
      </tr>
      <tr>
        <td align=right bgcolor=#eeeeee>�̸���</td> 
        <td> <input type=text size=15 name=email></td>
      </tr> 
      <tr>
        <td align=right bgcolor=#eeeeee>����ó</td> 
        <td> <input type=text size=15 name=phone></td>
      </tr>              
      <tr>
        <td align=right colspan=2> 
          <img src=./images/join.gif style="border:0" alt="���" onfocus='this.blur()'  onClick="SubmitForm();" > 
        </td>
      </tr>
    </table> 
  </form> 
  </body> 
</html>