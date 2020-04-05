<%
	Option Explicit
  Response.Expires=-1
  
  '개발자 페이지는 "rev" 계정으로만 접근 가능하다
  if Session("id") <> "rev" then
%>
  <script language="JavaScript">
    alert("권한이 없습니다.")
    history.back();
  </script>
<%  
  else
%>
	<!--#include file="./config/dbconfig.asp"--> 
<%

  'DB Connection
  Dim adoDb, objRS, SQL
  Set adoDb = Server.CreateObject("ADODB.Connection")
  
  adoDb.Open strConnect
  
	SQL = "select * from Content"
	Set objRs = adoDb.Execute(SQL) 
%>
<html>
	<head>
		<title>레브랜드</title>
		<!-- 스타일 시트를 사용한다 -->
		<link rel="stylesheet" href="./stylesheet/style.css">
	</head>
	<body>
	<h3>레브랜드</h3>
	"rev" 계정으로 로그인 했네요.<br>
	이 계정으로 로그인을 하면 개발자 페이지를 보실 수 있어요.<br>
	이 페이지에서 레브 게임의 각 프로젝트 추가, 업데이트, 삭제를 할 수 있네요.<br>
	<br>
	작업을 마친 후에는 로그오프를 하세요.<br>
	<br>
	<a href="./login/logout.asp"><img src="images/logout.gif" border=0></a>
	<br>
	<br>
	등록된 레브게임 목록입니다<br>
	데이터베이스 : [RevGame], 테이블 : [Content]<br><br>
	<table cellspacing=1 cellpadding=3 bgcolor=bule>
	<tr bgcolor="efefef" align="center">
		<td><b>idx</b></td>
		<td><b>strContentName</b></td>
		<td><b>nVersion</b></td>
		<td><b>dateReg</b></td>
		<td><b>dateUpdate</b></td>
		<td><b>textMemo</b></td>
		<td><b>업데이트</b></td>
	</tr>
<%	
 	Do until objRs.EOF
%>
	<form name="update" action="dep_update.asp" method="post" enctype="multipart/form-data">		
	<tr bgcolor="white" align="center">
		<td><%=objRs("idx")%></td>
		<td><%=objRs("strContentName")%></td>
		<td><%=objRs("nVersion")%></td>
		<td><%=objRs("dateReg")%></td>
		<td><%=objRs("dateUpdate")%></td>
		<td><%=objRs("textMemo")%></td>
		<td>
			<input type="hidden" name="strContentName" value="<%=objRs("strContentName")%>">
			<input type="hidden" name="nVersion" value="<%=objRs("nVersion")%>">
			<input type="file" name="attachFile" size = "7">
			<Input type="submit" value="업로드" style="cursor:hand">
		</td>
	</tr>
	</form>		 
<%		
		objRs.Movenext
	Loop
%>
	</body>
	</html>
<% 
	end if
%>
