<%
  Option Explicit
  Response.Expires=-1
%>
<!--#include file="../config/dbconfig.asp"--> 

<%
  'Query Request
  Dim id, pwd
 
  id = Request.form("id")
  pwd = Request.form("pwd")

  'DB Connection
  Dim adoDb, objRS, SQL
  Set adoDb = Server.CreateObject("ADODB.Connection")
  
  adoDb.Open strConnect
  
  SQL = "select count(*) from Member where strUserID ='" & id & "'"
  
  Set objRs = adoDb.Execute(SQL)
  
  'Not exist ID
  if objRs(0) = 0 then
%>
  <script language="JavaScript">
    alert("ID�� �������� �ʽ��ϴ�")
    history.back();
  </script>
<%    
  else
  
  SQL = "select * from Member where strUserID ='" & id & "'"
  Set objRs = adoDb.Execute(SQL)
  
  'Not correct password
  if not Trim(Request("pwd")) = Trim(objRs("strPwd")) then
%>
  <script language="JavaScript">
    alert("��й�ȣ�� ��ġ���� �ʽ��ϴ�")
    history.back();
  </script>
<%  
  'authentication  
  else

	'session setting
	Session("id") = id
	Session("name") = objRs("strUserName")

  '���̵� "rev"�� ��쿣 ������ �������� �̵��Ѵ�
  if id = "rev" then
  
		Response.Redirect "../dep_main.asp"
  
  else
  
		Response.Redirect "../index.asp"
		
	end if

  end if  'for password wrong
  end if  'for id not exist
  
  objRs.close
  adoDB.Close
  Set objRs = nothing
  Set adoDB = nothing
%>