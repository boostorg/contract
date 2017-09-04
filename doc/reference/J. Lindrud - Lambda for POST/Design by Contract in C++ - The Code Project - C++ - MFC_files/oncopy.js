// Hook-up to the document.body.oncopy event,
// or in the <body>'s "oncopy" attribute.
// Author: Heath Stewart
function copyCode()
{
	try
	{
		var range = document.selection.createRange();
		if (document.selection.type != "none")
		{
			var parent = range.parentElement();
			var parentName = parent.tagName;
			if (parentName != null)
			{
				if (parentName.toLowerCase() == "pre")
				{
					// Replace superfluous <br> tags in a <pre> block.
					var re = /<br>/gi;
					var code = range.htmlText.replace(re, "\r\n");

					// Replace non-breaking spaces.
					re = /&nbsp;/gi;
					code = code.replace(re, " ");

					// Replace & characters.
					re = /&amp;/gi;
					code = code.replace(re, "&");

					// Replace < characters.
					re = /&lt;/gi;
					code = code.replace(re, "<");

					// Replace > characters.
					re = /&gt;/gi;
					code = code.replace(re, ">");
					
					// CJM: Remove colorization
					re = /<\/?span([^>])*>/gi;
					code = code.replace(re, "");

					if (code != null)
					{
						window.event.returnValue = false;
						window.clipboardData.setData("Text", code);
					}
				}
			}
		}
	}
	catch(e) {}
}
