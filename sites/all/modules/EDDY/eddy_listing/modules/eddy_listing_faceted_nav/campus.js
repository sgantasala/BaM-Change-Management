(function ($) {

	//Get Query String Param
	function getQuerystring(key, default_) {
		if (default_ == null) default_ = "";
		key = key.replace(/[\[]/, "\\\[").replace(/[\]]/, "\\\]");
		var regex = new RegExp("[\\?&]" + key + "=([^&#]*)");
		var qs = regex.exec(window.location.href);
		if (qs == null)
			return default_;
		else
			return qs[1];
	}

	function eddy_listings_campus(data){	
		if(data > 0) jQuery('#edit-zipcode').val(data);
	}
	
	//Slider
	var mySlider;

	$(document).ready(function(){

		//Filter the Campus List By Zip Code.
		try{
			
			if(Drupal.settings.hasOwnProperty('eddy_listing_requests')){
			
				var requestString = "";
				$.each( Drupal.settings.eddy_listing_requests, function( key, value ) {

					if(value.length > 0 && (key == 'type' || key == 'campus_type' || key == 'level' || key == 'category' || key == 'subject')){
						
						requestString += '&';
						requestString += key + "=" + value.toString();

					}
					
				});
				
				if($.cookie("user_postal_code") && $.cookie("user_radius")){
					requestString += '&radius=' + $.cookie("user_radius");
					requestString += '&postal_code=' + $.cookie("user_postal_code");
				}
				
				var allowed_methods = ['level', 'category', 'subject'];
				methods = [];
				$.each( allowed_methods, function( key, value ) {

					if($('.faceted-nav-' + value).length > 0){
						methods.push(value);
					}
				
				});

				if(methods.length > 0){
					$.ajax({
						type: 'GET',
						url: Drupal.settings.basePath + 'eddy-listing-ajax/get-faceted-nav-entity-multiple/?methods=' + methods.toString() + requestString,
						dataType: 'json',
						//cache: false,
						success:function(data){

							$.each( data, function( key, value ) {
								
								if(value.count > 0){
									
									$.each( $('.faceted-nav-' + value.name).find('li'), function( key3, li ) {
										
										//if($.inArray(parseInt($(li).attr("data-is-id")), value.results) === -1){
										if($.inArray(parseInt($(li).attr("data-is-id")), value.results) === -1 && $(li).attr("data-is-id") != "6" && $(li).attr("data-is-id") != "5"){
											//$(this).css("background", "green");
											$(this).remove();
										}
									
									});
								
								}
								
								$('.faceted-nav-' + value.name).closest(".block-eddy-listing-faceted-nav").css("visibility", "visible");
							
							});

						},			 
					});
				}
				
			}else{
			
				$("#block-eddy-listing-faceted-nav-eddy-faceted-nav-levels, #block-eddy-listing-faceted-nav-eddy-faceted-nav-categories, #block-eddy-listing-faceted-nav-eddy-faceted-nav-subjects").css("visibility", "visible");
			
			}

		}catch(e){}
		
		var zip = 0;
		
		//Removed Zip Code detection until further notice.
		if($("#get-zip-code-search-form, #get-zip-code-search-form-horizontal").length > 0){
		
			if(getQuerystring("zipcode")){
				
				zip = getQuerystring("zipcode");
				
				$('#edit-zipcode').val(zip);
				$.cookie("user_postal_code", zip, { expires: 100, path: '/' });
			}
			else if ($.cookie("user_postal_code")){
				
				$('#edit-zipcode').val($.cookie("user_postal_code"));
			}
			else{		
				if(typeof eddy_maxmind_get_postal_code == "function"){

					eddy_maxmind_get_postal_code(eddy_listings_campus);
                
				}
			}
			
		}

		var counterValue;
		
		if($("#get-zip-code-search-form, #get-zip-code-search-form-horizontal").length > 0){
		
			mySlider = new Slider('campus-slider', { 
			
				animationCallback: function(value){  
					
					counterValue = Math.round(value * 100);
					
					$(".campus-slider-counter").html(counterValue + " mi" + '<input type="hidden" id="counter-hidden-value" value="' + counterValue + '" />');
					
					set_right_left_side_class(counterValue);

				},
				callback: function(value){  
					
					$.cookie("user_radius", $("#counter-hidden-value").val(), { expires: 100, path: '/' });
					
					if ($.cookie("user_postal_code")){
					
						$.updateListings("update");
						
						if($('.group-campus-programs').length != 0 && $('.group-campus-programs.horizontal-tab-hidden').length == 0){
									
							remove_campus_filter_to_bottom($('.group-campus-programs #block-eddy-listing-faceted-nav-eddy-faceted-nav-campus-h'));
						
						}
						if($('.group-campus-locations').length != 0 && $('.group-campus-locations.horizontal-tab-hidden').length == 0){
							
							remove_campus_filter_to_bottom($('.group-campus-locations #block-eddy-listing-faceted-nav-eddy-faceted-nav-campus-h'));
						
						}
					}
				}
				
			});
			
		}

		//Sets Radius values
		var radius = 25;
		
		if(getQuerystring("radius")){
			radius = getQuerystring("radius");
			$.cookie("user_radius", radius, { expires: 100, path: '/' });
		}
		else if($.cookie("user_radius")){
			radius = $.cookie("user_radius");
		}
		else{
			$.cookie("user_radius", radius, { expires: 100, path: '/' });
		}
			
		var startingPoint = radius * .01;
		
		counterValue = Math.round(startingPoint * 100);
		

		if($("#get-zip-code-search-form, #get-zip-code-search-form-horizontal").length > 0)
			mySlider.setValue(startingPoint);
		
		
		$(".campus-slider-counter").html(counterValue + " mi" + '<input type="hidden" id="counter-hidden-value" value="' + counterValue + '" />');
		
		set_right_left_side_class(counterValue);

		$("#get-zip-code-search-form .form-submit, #get-zip-code-search-form-horizontal .form-submit").live('click', function(event){
		
			event.preventDefault();

			$(this).parents('form').find('.zipcode-error').remove();

			if($.cookie("user_postal_code") != $('#edit-zipcode').val()){ //Condition Added so service calls are not made when Zip Codes do not change.

				//zip code validation jsonp ajax call
				$.ajax({
					 type: 'GET',
					 url: Drupal.settings.form_engine_service + "/FormValidation/GetCityStateCountry?ZipCode=" + $('#edit-zipcode').val(),
					 dataType: 'jsonp', // Notice! JSONP <-- P (lowercase)
					 cache: false,
					 success:function(data){
					 
						if(data.length > 0){

							$.cookie("user_radius", $("#counter-hidden-value").val(), { expires: 100, path: '/' });
							$.cookie("user_postal_code", $('#edit-zipcode').val(), { expires: 100, path: '/' });
							$.updateListings("update");

							//if validation is successful, move zipcode filter to end on school detail page
							if($('.group-campus-programs').length != 0 && $('.group-campus-programs.horizontal-tab-hidden').length == 0){
								
								remove_campus_filter_to_bottom($('.group-campus-programs #block-eddy-listing-faceted-nav-eddy-faceted-nav-campus-h'));
							}

							if($('.group-campus-locations').length != 0 && $('.group-campus-locations.horizontal-tab-hidden').length == 0){
								
								remove_campus_filter_to_bottom($('.group-campus-locations #block-eddy-listing-faceted-nav-eddy-faceted-nav-campus-h'));
							}
							
						}else{		

							$('<div class="zipcode-error">Please enter a valid U.S. zip code</div>').insertAfter($('#get-zip-code-search-form .form-item-zipcode, #get-zip-code-search-form-horizontal .form-item-zipcode'));
							
						}
					 },					 
					 

				});
			
				
			}
			
		});
		
		function set_right_left_side_class(counterValue){
		
			$(".campus-slider-counter").removeClass("campus-slider-counter-right").removeClass("campus-slider-counter-left");
		
			if(counterValue == 100)
				$(".campus-slider-counter").addClass("campus-slider-counter-right");
			else if(counterValue == 0)
				$(".campus-slider-counter").addClass("campus-slider-counter-left");
				
		}
		
		function remove_campus_filter_to_bottom(obj){
			$('.region.region-content').append(obj);
			$(obj).hide();
			$('.messages.warning').remove();
		}
	

        $('#edit-zipcode').keyup(function () {
            $(this).val($(this).val().replace(/[^\d]/g, ''));
        });

	});
	
})(jQuery);