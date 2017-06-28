
(function ($) {
	$(document).ready(function(){
	
		//inactive select with inactive class name
		$('.qdf-holder select.inactive').attr("disabled","disabled");
		$('.qdf-holder select.hide').parent().hide();
		
		
		//not allow to choose subject as the first question in degree QDF
		$('.qdf-holder select[name="1[qq_type]"]').children('option[value=subject]').attr('disabled', true);
		//not allow to choose subject as the first question in career QDF
		$('.qdf-holder select[name="1[qq_type]"]').children('option[value=occupation]').attr('disabled', true);
		
		
		//add inline class
		$('.qdf-holder .form-item .inline').parents('div.form-item').addClass('inline');
		
		
		// QSB Type of Campus and Career will temporary disabled
		$('#edit-qsb-type-campus, #edit-qsb-type-career').attr("disabled","disabled");
		$('#edit-qsb-type-campus, #edit-qsb-type-career').click(function(){
			alert("Campus and Career are temporarily unavailable");
			return false;
		});
		
		
		//Fill in default field label when select question type 
		$('.qdf-holder select[name*="[qq_type]"]').change(function(event){
			var field_label = "";
			switch ($(this).val()){
				case 'category':
					field_label = "-- Select a Category --";
					break;
				case 'subject':
					field_label = "-- Select a Subject --";
					break;
				case 'degree':
					field_label = "-- Select Degree Level --";
					break;	
				case 'industry':
					field_label = "Select Industry";
					break;	
				case 'occupation':
					field_label = "Select Occupation";
					break;					
			}
			$(this).parents('div.fieldset-wrapper').find('input[name*="qq_field_label"]').val(field_label);
		});
		
		/* QDF Style SETUP */
		$('#qdf_style_container #edit-color').change(function(event){
			$('#qdf_style_preview_container .qdf_style_preview.color').removeClass().addClass($(this).val()).addClass('qdf_style_preview color');
		});
		$('#qdf_style_container #edit-question-align input').change(function(event){
			$('#qdf_style_preview_container .question-align').removeClass().addClass($(this).val()).addClass('question-align');
		});
		
		$('#qdf_style_container #edit-title-align input').change(function (event) {
		    $('#qdf_style_preview_container .block-title').removeClass().addClass($(this).val()).addClass('block-title');
		});

		$('#qdf_style_container #edit-button-align input').change(function (event) {
		    $('#qdf_style_preview_container .submit-button').removeClass().addClass($(this).val()).addClass('submit-button');
		});

		$('#qdf_style_container #edit-form-position input').change(function (event) {
		    $('#qdf_style_preview_container .qdf-holder').removeClass().addClass($(this).val()).addClass('qdf-holder');
		});
		$('#qdf_style_container #edit-image-position input').change(function (event) {
		    $('#qdf_style_preview_container .qdf_style_preview').removeClass().addClass($(this).val()).addClass('qdf_style_preview');
		});

		$('#qdf_style_container #edit-button-skin').change(function (event) {
		    $('#qdf_style_preview_container .submit-button input').removeClass().addClass($(this).val()).addClass('form-select');
		});
		$('#qdf_style_preview_container .submit-button input').click(function(event){

			event.preventDefault();
			return false;
		});
		
	});
	//end of document ready

})(jQuery);
