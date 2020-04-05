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
  
  '업로드를 처리할 오브젝트를 생성합니다.
  Set Upload = Server.CreateObject("TABS.Upload")
 '업로드를 시작합니다.
  Upload.Start DirectoryPath
 
 'Request Form
  Dim strContentName, nVersion, strSaveName
  
  'file upload
  strContentName = Upload.Form("strContentName")
  nVersion			 = Upload.Form("nVersion")
  
  '한단계 버젼 업데이트한 파일명으로 저장한다
  
	nVersion = nVersion + 1
	strSaveName = "D:\RevGame\FTP\Update\"& strContentName & "\" & strContentName & nVersion & ".zip"
	
  If Upload.Form("attachFile").FileSize <> 0 Then
    
    '업로드된 파일을 디스크에 저장합니다.
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