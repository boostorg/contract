// $ Id: $

Drupal.toggleTOC = function(toc) {
  $('#tocbody').toggle();
  if ($('#tocbody').is(':visible')) {
    $('#toctoggle').empty().append('[hide]');
  } else {
    $('#toctoggle').empty().append('[show]');
  }
}

if (Drupal.jsEnabled) {
  $(document).ready(function() {
    $('#toctitle').each(function() {
      $(this).append($('<a style="margin-left:1em;font-size:smaller" id="toctoggle" href="#">[hide]</a>').click(function(){Drupal.toggleTOC();}));
    });
  });
}
