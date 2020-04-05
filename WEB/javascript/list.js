var dragswitch=0 
var nsx 
var nsy 
var nstemp 

function drag_dropns(name)
{ 
  temp=eval(name) 
  temp.captureEvents(Event.MOUSEDOWN | Event.MOUSEUP) 
  temp.onmousedown=gons 
  temp.onmousemove=dragns 
  temp.onmouseup=stopns 
} 

function gons(e)
{ 
  temp.captureEvents(Event.MOUSEMOVE) 
  nsx=e.x 
  nsy=e.y 
} 

function dragns(e)
{ 
  if (dragswitch==1)
  { 
    temp.moveBy(e.x-nsx,e.y-nsy) 
    return false 
  } 
} 

function stopns()
{ 
  temp.releaseEvents(Event.MOUSEMOVE) 
} 

var dragapproved=false 

if ( document.all )
{ 
  document.onmouseup=new Function("dragapproved=false") 
} 

// Comment를 추가합니다
function addComment(QSPage)
{
  var name = document.frmMent.name.value;
  if (CheckStr(name, " ", "")==0) 
  {
    alert("제목을 입력해 주세염");
    document.frmMent.name.focus();
    return false;
  }
  var email = document.frmMent.email.value;
  if (CheckStr(email, " ", "") !=0 ) 
  {
    if( check_email(email) == 0 )
    {
      document.frmMent.email.focus();
      return false;
    }
  }
  var content = document.frmMent.content.value;
  if (CheckStr(content, " ", "")==0) 
  {
    alert("내용을 입력해 주세염");
    document.frmMent.content.focus();
    return false;
  }
  var pwd = document.frmMent.pwd.value;
  if (CheckStr(pwd, " ", "")==0) 
  {
    alert("비밀번호를 입력해 주세염");
    document.frmMent.pwd.focus();
    return false;
  }

  var attachFile = document.frmMent.attachFile.value;
  if (CheckStr(attachFile, " ", "") > 0)  
  {
    document.all.divUpload.style.display    = ""
    document.all.divUpload.style.pixelTop  = document.all.divWrite.style.pixelTop + (document.all.divWrite.offsetHeight - document.all.divUpload.offsetHeight)/2;
    document.all.divUpload.style.pixelLeft  = document.all.divWrite.style.pixelLeft + (document.all.divWrite.offsetWidth - document.all.divUpload.offsetWidth)/2;
  }
  document.frmMent.action ="../taboard/Insert.asp?QSPage="+QSPage
  document.frmMent.submit();
}
  
// Comment를 수정합니다
function modifyComment(QSPage)
{
  var name = document.frmModify.name.value;
  if (CheckStr(name, " ", "")==0) 
  {
    alert("제목을 입력해 주세염");
    document.frmModify.name.focus();
    return false;
  }
  var email = document.frmModify.email.value;
  if (CheckStr(email, " ", "") !=0 ) 
  {
    if( check_email(email) == 0 )
    {
      document.frmModify.email.focus();
      return false;
    }
  }    
  var content = document.frmModify.content.value;
  if (CheckStr(content, " ", "")==0) 
  {
    alert("내용을 입력해 주세염");
    document.frmModify.content.focus();
    return false;
  }
  var pwd = document.frmModify.pwd.value;
  if (CheckStr(pwd, " ", "")==0) 
  {
    alert("비밀번호를 입력해 주세염");
    document.frmModify.pwd.focus();
    return false;
  }
  
  var attachFile = document.frmModify.attachFile.value;
  if (CheckStr(attachFile, " ", "") > 0)  
  {
    document.all.divUpload.style.display    = ""
    document.all.divUpload.style.pixelTop  = document.all.divModify.style.pixelTop + (document.all.divModify.offsetHeight - document.all.divUpload.offsetHeight)/2;
    document.all.divUpload.style.pixelLeft  = document.all.divModify.style.pixelLeft + (document.all.divModify.offsetWidth - document.all.divUpload.offsetWidth)/2;
  }   
  document.frmModify.action ="../taboard/update.asp?QSPage="+QSPage
  document.frmModify.submit();
}
  
// Comment를 삭제합니다
function delComment()
{
  var pwd = document.frmDel.pwd.value;
  if (CheckStr(pwd, " ", "")==0) 
  {
    alert("비밀번호를 입력해 주세염");
    document.frmDel.pwd.focus();
    return false;
  }
  document.frmDel.submit();
}
  
// 문자열 체크를 합니다
function CheckStr( strOriginal, strFind, strChange )
{
  var position, strOri_Length;
  position = strOriginal.indexOf(strFind); 

  while (position != -1)
  {
    strOriginal = strOriginal.replace(strFind, strChange);
    position = strOriginal.indexOf(strFind);
  }

  strOri_Length = strOriginal.length;
  return strOri_Length;
}
  
// 이메일 유효성 체크 함수 
function check_email(email) 
{ 
  if (!validate_ascii_data(email)) 
  { 
    alert("E-Mail에 잘못된 문자가 있습니다. 다시 입력해 주십시오."); 
    return false 
  } 
  var invalidChars = "\"|&;<>!*\'\\"; 
    
  for (var i = 0; i < invalidChars.length; i++) 
  { 
    if (email.indexOf(invalidChars.charAt(i)) != -1) 
    { 
      alert("E-Mail에 잘못된 문자가 있습니다. 다시 입력해 주십시오."); 
      return false; 
    } 
  } 
    
  if (email.indexOf("@")==-1)
  { 
    alert("E-Mail이 잘못되었습니다. '@'가 있는지 확인해 주십시오."); 
    return false; 
  } 
    
  if (email.indexOf(" ") != -1)
  { 
    alert("E-Mail에 공백이 있습니다. 다시 입력해 주십시오."); 
    return false; 
  } 
    
  if(window.RegExp) 
  { 
    var reg1str = "(@.*@)|(\\.\\.)|(@\\.)|(\\.@)|(^\\.)"; 
    var reg2str = "^.+\\@(\\[?)[a-zA-Z0-9\\-\\.]+\\.([a-zA-Z]{2,3}|[0-9]{1,3})(\\]?)$"; 
    var reg1 = new RegExp (reg1str); 
    var reg2 = new RegExp (reg2str); 
    if (reg1.test(email) || !reg2.test(email)) 
    { 
      alert("E-Mail에 잘못된 문자가 있습니다. 다시 입력해 주십시오."); 
      return false; 
    } 
  } 
  return true; 
}
   
function validate_ascii_data(urstr) 
{ 
  var i; var result; 
  for(i=0; i<urstr.length; i++) 
  { 
    if((urstr.charAt(i) < " ") || (urstr.charAt(i) > "~"))
    return false; 
  } 
  return true; 
} 
  
// 쓰기폼 레이어
function showWriteForm( group, align, magin_left )
{
  document.all.divWrite.style.display    = ""    
  document.all.divWrite.style.pixelTop  = document.body.scrollTop + (document.body.clientHeight - document.all.divWrite.offsetHeight)/2 + 50;
  if ( align == "center" )
{
  document.all.divWrite.style.pixelLeft  = document.body.scrollLeft+ (document.body.clientWidth - document.all.divWrite.offsetWidth)/2 + magin_left;

}
else
{
  document.all.divWrite.style.pixelLeft  = document.body.scrollLeft+magin_left;

}

  document.frmMent.group.value      = group
  document.frmMent.name.focus();
}

function initializeWriteDragie()
{ 
  iex=event.clientX 
  iey=event.clientY 
  tempx=divWrite.style.pixelLeft 
  tempy=divWrite.style.pixelTop 
  dragapproved=true 
  document.onmousemove=dragWriteDropie 
} 

function dragWriteDropie()
{ 
  var x, y;
  if (dragapproved==true)
  { 
    if (tempx+event.clientX-iex  > 10)
    {
      x = tempx+event.clientX-iex;
    }
    else
    {
      x=10;
    }
    if(tempy+event.clientY-iey >10)
    {
      y=tempy+event.clientY-iey;
    }
    else
    {
      y=10;
    }
    document.all.divWrite.style.pixelLeft=x
    document.all.divWrite.style.pixelTop=y
    return false 
  } 
} 


// 수정폼 레이어
function showModifyForm( idx, align, name, email, content, magin_left )
{
  document.all.divModify.style.display  = ""
  document.all.divModify.style.pixelTop  = document.body.scrollTop + (document.body.clientHeight - document.all.divModify.offsetHeight)/2 + 50;
  document.all.divModify.style.pixelLeft  = document.body.scrollLeft+magin_left;
  document.frmModify.idx.value      = idx
  document.frmModify.name.value      = name
  document.frmModify.email.value    = email
  document.frmModify.content.value  = content
  document.frmModify.name.focus();
}

function initializeModifyDragie()
{ 
  iex=event.clientX 
  iey=event.clientY 
  tempx=divModify.style.pixelLeft 
  tempy=divModify.style.pixelTop 
  dragapproved=true 
  document.onmousemove=dragModifyDropie 
} 

function dragModifyDropie()
{ 
  var x, y;
  if (dragapproved==true)
  { 
    if (tempx+event.clientX-iex  > 10)
    {
      x = tempx+event.clientX-iex;
    }
    else
    {
      x=10;
    }
    if(tempy+event.clientY-iey >10)
    {
      y=tempy+event.clientY-iey;
    }
    else
    {
      y=10;
    }
    document.all.divModify.style.pixelLeft=x
    document.all.divModify.style.pixelTop=y
    return false 
  } 
} 
  
// 삭제폼 레이어
function showDelForm( idx )
{
  document.all.divDel.style.display    = ""
  document.all.divDel.style.pixelTop  = document.body.scrollTop + (document.body.clientHeight - document.all.divDel.offsetHeight)/2 + 50
  document.all.divDel.style.pixelLeft  = document.body.scrollLeft + 350;
  document.frmDel.idx.value            = idx
  document.frmDel.pwd.focus();
}

function initializeDelDragie()
{ 
  iex=event.clientX 
  iey=event.clientY 
  tempx=divDel.style.pixelLeft 
  tempy=divDel.style.pixelTop 
  dragapproved=true 
  document.onmousemove=dragDelDropie 
} 

function dragDelDropie()
{ 
  var x, y;
  if (dragapproved==true)
  { 
    if (tempx+event.clientX-iex  > 10)
    {
      x = tempx+event.clientX-iex;
    }
    else
    {
      x=10;
    }
    if(tempy+event.clientY-iey >10)
    {
      y=tempy+event.clientY-iey;
    }
    else
    {
      y=10;
    }
    document.all.divDel.style.pixelLeft=x
    document.all.divDel.style.pixelTop=y
    return false 
  } 
}

//글씨 깜박꺼리기 관련 사용할땐 <blink>~</blink> 로 해주세요
function doBlink() 
{ 
  var blink = document.all.tags("BLINK") 
  for (var i=0; i < blink.length; i++) 
  blink[i].style.visibility = blink[i].style.visibility == "" ? "hidden" : "" 
} 

function startBlink() 
{ 
  if (document.all) 
  setInterval("doBlink()",500)
} 

window.onload = startBlink; 
