var isIE = navigator.appName.indexOf("Microsoft") != -1;
var GLastActiveNode = "";

function nsOpenTreeItem(itemname)
{
    var element = document.getElementById("plusImg_" + itemname.id);
    element.style.visibility = "hidden";
    element.style.display = "none";

    element = document.getElementById("minusImg_" + itemname.id);
    element.style.visibility = "visible";
    element.style.display = "";

	element = document.getElementById("Childs_" + itemname.id);
    element.style.visibility = "visible";
    element.style.display = "";
}

function nsCloseTreeItem(itemname)
{
    var element = document.getElementById("plusImg_" + itemname.id);
    element.style.visibility = "visible";
    element.style.display = "";

    element = document.getElementById("minusImg_" + itemname.id);
    element.style.visibility = "hidden";
    element.style.display = "none";

	element = document.getElementById("Childs_" + itemname.id);
    element.style.visibility = "hidden";
    element.style.display = "none";
}

function nsloadIframe(node)
{

  if (GLastActiveNode != "")
  {
    if (isIE)
    {
      GLastActiveNode.setAttribute('className','nsTreeNode');
    }
    else
    {
      GLastActiveNode.setAttribute('class','nsTreeNode');
    }
  }
  if (isIE)
  {
    node.setAttribute('className','nsBoldNode');
  }
  else
  {
    node.setAttribute('class','nsBoldNode');
  }

  GLastActiveNode = node;
  return true;
}