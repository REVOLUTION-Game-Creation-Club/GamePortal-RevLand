<%
  Option Explicit
  Response.Expires=-1
%>
<!--#include file="./config/dbconfig.asp"--> 
<%

  'DB Connection
  Dim adoDb, objRS, SQL
  Set adoDb = Server.CreateObject("ADODB.Connection")
  
  adoDb.Open strConnect
  
  '���� ���� Content �ε�
 
	function GetVersion(strContentName)
		Dim nVersion
		SQL = "select nVersion from Content where strContentName = '"& strContentName &"'"
		Set objRs = adoDb.Execute(SQL)   
		
		if Not objRs.EOF then
			nVersion = objRs(0)
		else
			nVersion = 0
		end if

		objRs.close
		Set objRs = nothing
		GetVersion = nVersion
  end function
  
  function GetScore(strUserID, strContentName)
	Dim nScore
		SQL = "select nScore from Score where strUserID = '"& strUserID &"' and strContentName = '"& strContentName &"'"
		Set objRs = adoDb.Execute(SQL)  

		if Not objRs.EOF then
			nScore = objRs(0)
		else
			nScore = 0
		end if

		objRs.close
		Set objRs = nothing
		GetScore = nScore
	end function

%>
<html>
  <head>
    <title>���귣��</title>
    <link rel="stylesheet" href="../stylesheet/style.css">
    
    <script language=javascript>
    <!--
      function CheckForm() { 
        if (document.login.id.value.length == 0) { 
          alert("���̵� �Է��Ͻÿ�."); 
          document.login.id.focus(); 
          return false; 
        } 
        if (document.login.pwd.value.length == 0) { 
          alert("��й�ȣ�� �Է��Ͻÿ�."); 
          document.login.pwd.focus(); 
          return false; 
        } 
        else { 
          document.login.action="./login/login_confirm.asp"
          document.login.submit(); 
          return true; 
        } 
      } 
      
      function SetFocus() {
        document.login.id.focus();
      }    

			function LanchContent(strUserID, strUserName, strContentName, dwVersion, dwScore)
			{
				if( document.Launcher != null && document.Launcher.object != null )
				{
					document.Launcher.LauchContent(strUserID, strUserName, strContentName, dwVersion, dwScore);
				}
			}
    //--> 
    </script> 
  </head>    

<% if Session("id") = "" then %>
  <body onload="SetFocus();">
	<h3>���귣��</h3>
		���귣�� ������ �ϱ� ���ؼ��� �α����� �ʿ��մϴ�<br>
		�ڽ��� ���̵�� ������ �ϸ� ������ ������ ����� �Ǳ� ��������<br>
		�¶��� ���� ��쿡�� ������ �ʿ��ϱ���<br>
		<br>
		������ ������ ���� ���̵� ���弼��<br>
		(���� ������� ����ʹ� �����Դϴ�)<br>
		������ ���� [���̵�], [���], [�̸�] �� �Է��Ͻø� �˴ϴ�<br>
		<br>
		
		<!-- �α� â -->

    <form method='post' name='login' onSubmit='Javascript:return CheckForm();'>
		  <table style="font-size:9pt" width="150" height="79" style="margin-left:100;">
		    <tr>
		      <td>���̵� :</td>
		      <td><input type='Text' name='id' size='8' style="border : solid 1 gray"></td> 
		    </tr>
		    <tr> 
		      <td>��й�ȣ :</td>
		      <td><input type='password' name='pwd' size='8' style="border : solid 1 gray"></td>
		    </tr>
		    <tr>
					<td colspan = 2 align = right>
						<input type='Image' name='Image' src="images/login.gif" style='border:0'>
						<a href="./login/login_new.asp"><img src="images/register.gif" border=0></a>
		        &nbsp;&nbsp;
		      </td>
		    </tr>
		  </table>
		</form>

		</p>

	</body>
<% 
	else 
	
%>
  <body>
	<h3>���귣��</h3>
	
<OBJECT id=Launcher style="LEFT: 0px; TOP: 0px" codeBase=launcher.CAB#version=1,0,0,8 
	height=15 width=50 classid="clsid:DD0B32E9-16DC-4C00-8238-8839594370A4">
	<PARAM NAME="_Version" VALUE="65536">
	<PARAM NAME="_ExtentX" VALUE="1323">
	<PARAM NAME="_ExtentY" VALUE="397">
	<PARAM NAME="_StockProps" VALUE="0"></OBJECT>
<br>
<br>
	���� -> ���ͳ� �ɼ� -> ���� <br>
	-> ����� ���� ���� -> ActiveX ��Ʈ�� �� �÷��� �� -> ���� �� �� ActiveX ��Ʈ�� �ٿ�ε�<br>
	���⿡�� "��� �� ��" -> "Ȯ��" ���� ������ �ּ���.<br>
	������ �ҷ��� ���� �� ��ٰ� �ϳ׿�..T.T<br>
	<br>
	http://revgame.knu.ac.kr �� ����ϼ���~~ ������ ���귣��� ����~
	<br>
	<br>
	�ȳ��ϼ���. <b style="color:orange;"><%=Session("name")%></b>��
	<br>
	<br>
		<a href="javascript:LanchContent(
						'<%=Session("id")%>',
						'<%=Session("name")%>',
						'pjmc', 
						<%=GetVersion("pjmc")%>, 
						<%=GetScore("pjmc", Session("id"))%>);">
		'04 [ ���帶�� ] ���� : <%=GetScore("pjmc", Session("id"))%></a>
		<br>
		<a href="javascript:LanchContent(
						'<%=Session("id")%>',
						'<%=Session("name")%>',						
						'shotbomb', 
						<%=GetVersion("shotbomb")%>, 
						<%=GetScore("shotbomb", Session("id"))%>);">
		'04 [ Shot & Bomb ] ���� : <%=GetScore("pjmc", Session("id"))%></a>
		<br>
		<br>

<a href="./login/logout.asp"><img src="images/logout.gif" border=0></a>
	</body>
<% 
	end if
%>
</html>

