jQuery(function ($) {

  'use strict';

  $(document).ready(function () {

      if ($('#js-editor-field textarea').length > 0) {

          var jsCreateEditor = CodeMirror.fromTextArea($('#js-editor-field textarea')[0], {
              lineNumbers: true,
              styleActiveLine: true,
              matchBrackets: true,
              mode: "javascript"
          });

      }

      if ($('#css-editor-field textarea').length > 0) {

          // Unobstrusive syntax highlighting
          var $textarea = $('#css-editor-field textarea');

          var createEditor = function () {
              var editor = CodeMirror.fromTextArea($textarea[0], { lineNumbers: true });
              editor.on('change', function (obj) { autoPreview(); });
              return editor;
          };

          var editor = createEditor();

          $textarea.before('<input type="checkbox" id="css-editor-toggle-editor" /> <label for="css-editor-toggle-editor">' + Drupal.t('Use plain text editor') + '</label>');

          $('#css-editor-toggle-editor').click(function () {
              if ($(this).is(':checked')) {
                  editor.toTextArea();
              }
              else {
                  editor = createEditor();
              }
          });

          // Preview
          var $preview = $('#css-editor-preview');
          $textarea.before('<input type="checkbox" id="css-editor-toggle-preview" checked="checked" /> <label for="css-editor-toggle-preview">' + Drupal.t('Enable auto preview.') + '</label>');

          $('#css-editor-toggle-preview').click(function () {
              if ($(this).is(':checked')) {
                  $preview.show();
                  autoPreview();
              }
              else {
                  $preview.hide();
              }
          });

          $textarea.keyup(function () { autoPreview(); });

          $preview.load(function () { autoPreview(); });

          var autoPreview = function () {
              if ($('#css-editor-toggle-preview').is(':checked')) {
                  var value = ($('#css-editor-toggle-editor').is(':checked') ? $textarea.val() : editor.getValue());
                  var id = 'css-editor-preview-style';
                  var $css = $preview.contents().find('#' + id);
                  if ($css.length) {
                      $css.html(value);
                  }
                  else {
                      $preview.contents().find('head').append($('<style type="text/css" id="' + id + '">' + value + '</style>'));
                  }
              }
          };

      }


  });

});
