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
  
  '레브 게임 Content 로드
 
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
    <title>레브랜드</title>
    <link rel="stylesheet" href="../stylesheet/style.css">
    
    <script language=javascript>
    <!--
      function CheckForm() { 
        if (document.login.id.value.length == 0) { 
          alert("아이디를 입력하시오."); 
          document.login.id.focus(); 
          return false; 
        } 
        if (document.login.pwd.value.length == 0) { 
          alert("비밀번호를 입력하시오."); 
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
	<h3>레브랜드</h3>
		레브랜드 게임을 하기 위해서는 로그인이 필요합니다<br>
		자신의 아이디로 게임을 하면 서버에 점수가 등록이 되기 때문이죠<br>
		온라인 겜일 경우에는 더더욱 필요하구요<br>
		<br>
		계정이 없으신 분은 아이디를 만드세요<br>
		(기존 레볼루션 멤버와는 별개입니다)<br>
		가입을 눌러 [아이디], [비번], [이름] 만 입력하시면 됩니다<br>
		<br>
		
		<!-- 로긴 창 -->

    <form method='post' name='login' onSubmit='Javascript:return CheckForm();'>
		  <table style="font-size:9pt" width="150" height="79" style="margin-left:100;">
		    <tr>
		      <td>아이디 :</td>
		      <td><input type='Text' name='id' size='8' style="border : solid 1 gray"></td> 
		    </tr>
		    <tr> 
		      <td>비밀번호 :</td>
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
	<h3>레브랜드</h3>
	
<OBJECT id=Launcher style="LEFT: 0px; TOP: 0px" codeBase=launcher.CAB#version=1,0,0,8 
	height=15 width=50 classid="clsid:DD0B32E9-16DC-4C00-8238-8839594370A4">
	<PARAM NAME="_Version" VALUE="65536">
	<PARAM NAME="_ExtentX" VALUE="1323">
	<PARAM NAME="_ExtentY" VALUE="397">
	<PARAM NAME="_StockProps" VALUE="0"></OBJECT>
<br>
<br>
	도구 -> 인터넷 옵션 -> 보안 <br>
	-> 사용자 지정 수준 -> ActiveX 컨트롤 및 플러그 인 -> 서명 안 된 ActiveX 컨트롤 다운로드<br>
	여기에서 "사용 안 함" -> "확인" 으로 변경해 주세요.<br>
	서명을 할려면 돈이 꽤 든다고 하네요..T.T<br>
	<br>
	http://revgame.knu.ac.kr 을 기억하세요~~ 조만간 레브랜드로 변신~
	<br>
	<br>
	안녕하세요. <b style="color:orange;"><%=Session("name")%></b>님
	<br>
	<br>
		<a href="javascript:LanchContent(
						'<%=Session("id")%>',
						'<%=Session("name")%>',
						'pjmc', 
						<%=GetVersion("pjmc")%>, 
						<%=GetScore("pjmc", Session("id"))%>);">
		'04 [ 포장마차 ] 점수 : <%=GetScore("pjmc", Session("id"))%></a>
		<br>
		<a href="javascript:LanchContent(
						'<%=Session("id")%>',
						'<%=Session("name")%>',						
						'shotbomb', 
						<%=GetVersion("shotbomb")%>, 
						<%=GetScore("shotbomb", Session("id"))%>);">
		'04 [ Shot & Bomb ] 점수 : <%=GetScore("pjmc", Session("id"))%></a>
		<br>
		<br>

<a href="./login/logout.asp"><img src="images/logout.gif" border=0></a>
	</body>
<% 
	end if
%>
</html>

