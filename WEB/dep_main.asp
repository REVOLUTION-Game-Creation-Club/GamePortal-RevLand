<%
	Option Explicit
  Response.Expires=-1
  
  '������ �������� "rev" �������θ� ���� �����ϴ�
  if Session("id") <> "rev" then
%>
  <script language="JavaScript">
    alert("������ �����ϴ�.")
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
		<title>���귣��</title>
		<!-- ��Ÿ�� ��Ʈ�� ����Ѵ� -->
		<link rel="stylesheet" href="./stylesheet/style.css">
	</head>
	<body>
	<h3>���귣��</h3>
	"rev" �������� �α��� �߳׿�.<br>
	�� �������� �α����� �ϸ� ������ �������� ���� �� �־��.<br>
	�� ���������� ���� ������ �� ������Ʈ �߰�, ������Ʈ, ������ �� �� �ֳ׿�.<br>
	<br>
	�۾��� ��ģ �Ŀ��� �α׿����� �ϼ���.<br>
	<br>
	<a href="./login/logout.asp"><img src="images/logout.gif" border=0></a>
	<br>
	<br>
	��ϵ� ������� ����Դϴ�<br>
	�����ͺ��̽� : [RevGame], ���̺� : [Content]<br><br>
	<table cellspacing=1 cellpadding=3 bgcolor=bule>
	<tr bgcolor="efefef" align="center">
		<td><b>idx</b></td>
		<td><b>strContentName</b></td>
		<td><b>nVersion</b></td>
		<td><b>dateReg</b></td>
		<td><b>dateUpdate</b></td>
		<td><b>textMemo</b></td>
		<td><b>������Ʈ</b></td>
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
			<Input type="submit" value="���ε�" style="cursor:hand">
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
