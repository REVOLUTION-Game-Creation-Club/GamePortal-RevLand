<%
   Option Explicit
  Response.Expires=-1 
%>

<!--#include file="./config/dbconfig.asp"-->   

<%
  'Setting upload folder
  Dim DirectoryPath
  DirectoryPath = "D:\RevGame\FTP\Update"
  
  Dim Upload
  
  '���ε带 ó���� ������Ʈ�� �����մϴ�.
  Set Upload = Server.CreateObject("TABS.Upload")
 '���ε带 �����մϴ�.
  Upload.Start DirectoryPath
 
 'Request Form
  Dim strContentName, nVersion, strSaveName
  
  'file upload
  strContentName = Upload.Form("strContentName")
  nVersion			 = Upload.Form("nVersion")
  
  '�Ѵܰ� ���� ������Ʈ�� ���ϸ����� �����Ѵ�
  
	nVersion = nVersion + 1
	strSaveName = "D:\RevGame\FTP\Update\"& strContentName & "\" & strContentName & nVersion & ".zip"
	
  If Upload.Form("attachFile").FileSize <> 0 Then
    
    '���ε�� ������ ��ũ�� �����մϴ�.
    Upload.Form("attachFile").SaveAs strSaveName, True

		'DB Connection
		Dim adoRs, strSQL
		Set adoRs = Server.CreateObject("ADODB.RecordSet")
		  
		strSQL = "select * from Content where strContentName = '" & strContentName & "'"
		adoRs.Open strSQL, strConnect, adOpenStatic, adLockPessimistic, adCmdText


		with adoRs
		  .Fields("nVersion")  = nVersion
		  .Fields("dateUpdate")= now()
		  .Update
		  .Close
		end with
  
		Set adoRs = nothing
  
  End if
    
  Response.Redirect "./dep_main.asp"
%>