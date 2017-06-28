
(function ($) {
	$(document).ready(function(){

		$('.front .qdf-holder .qsb-question select').live("change", function(){
			_etq.push(['_etEvent', 'change-dropdown', 'qdf', 'homepage', '']);
		});
		
		$(".qdf-holder form.qdf-block-form").live("submit", function (e) {	
					
			if(form_validate($(this))){
				_etq.push(['_etEvent', 'submit-form', 'qdf', 'homepage', '']);
				e.preventDefault()//return false;
			}else{				
				e.preventDefault();//return false;
			}
			
		//
		});
	
	
	
		function form_validate(formObj){		
			//will check validation if this is a Degree qsb and submit to school form page
			if(Drupal.settings.appName == "elearners"){
				var questions = formObj.find(".qdf-block-form-item");

				for(var i =0; i < questions.length; i++){
					if($(questions[i]).val() == "-1"){						
						return false;
					}
				}
			}
			
			return true;
		}
	
	});
	//end of document ready

})(jQuery);
