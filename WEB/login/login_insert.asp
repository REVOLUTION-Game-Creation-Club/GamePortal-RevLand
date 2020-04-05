<%
  Option Explicit 
%>
  <!--#include file="../config/dbconfig.asp"--> 
<%
  'Request Form
  Dim id, name, pwd, email, phone
  id  	= Request.form("id")
  name  = Request.form("name")	  
  pwd		= Request.form("pwd")
  email = Request.Form("email")
  phone = Request.Form("phone")
  
  'DB Connection
  Dim adoRs
  Set adoRs = Server.CreateObject("ADODB.RecordSet")
  adoRs.Open "Member", strConnect, adOpenStatic, adLockPessimistic, adCmdTable
  
  with adoRs
    .AddNew
    .Fields("strUserID")   = id
    .Fields("strUserName") = name
    .Fields("strPwd")      = pwd
    .Fields("strEmail")		 = email
    .Fields("strPhone")		 = phone
    .Fields("dateReg")     = now()
    .Update
    .Close
  end with

  Set adoRs = nothing
  Session("id") = id
  Session("name") = name
  Response.Redirect "../index.asp"
%>
