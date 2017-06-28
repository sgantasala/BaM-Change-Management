
#Using the Toaster Ad
 
**Inside Optimizly or when loading after jQuery and Toaster Scripts:

<script type="text/javascript">

(function ($) {

	$(document).ready(function () {

		$.toaster.init({
			html: "<h1>Hello World</h1>", //Required, The HTML that you want to have appear. For a DFP Ad, just add a rendering Div and incldue the display method in the complete property.
			background: 'blue', //(Optional) Default is Black.
			slide_duration: 2000, //(Optional) Default is 1000.
			delay: 1000, //(Optional) Delay in Show. Default 1000.
			padding: '20px', //(Optional) Default 10px.
			cookie_expires: 4, //(Optional) Default per session.
			button_text_color: blue, //(Optional) Close Button Text Color Default #ccc.
			button_background: black, //(Optional) Close Button Background Color Default transparent.
			z_index: 100, //(Optional) z-index of the Toaster Ad. Default 100.
			complete: function () { //(Optional) Callback when the Ad Displays after the delay. Ad code with display method should be placed in here.
			   // alert("Hello");
			}
		});

		#Using the interstitial Ad
		#for trig by step: set trig_by_step: true and put below code into THANKYOU workflow of OptimizelyPageCustomization callback function
		jQuery.interstitial.init({
            id:"interstitial_ads",
            html: "<h1>Hello World</h1>", //Required, The HTML that you want to have appear. For a DFP Ad, just add a rendering Div and incldue the display method in the complete property.
            loading_text: '<h3>Loading</h3>', //Loading text, will be replaced by ads itself. Default 'Loading...'
            background: "#999",
            fade_duration: 1000, //(Optional) Default is 500.
            delay: 100, //(Optional) Delay in Show. Default 1000.
            cookie_expires: 0, //(Optional) Default per session.
            button_text_color: 'white', //(Optional) Close Button Text Color Default #ccc.
            button_background: 'red', //(Optional) Close Button Background Color Default transparent.
            z_index: '9999', //(Optional) z-index of the Toaster Ad. Default 9999.
            box_init_position: 'width:50%; height:65%; top:17%; left:25%;', //(Optional) maually set box width, height, top, and left. Default 'width:50%; height:50%; top:25%; left:25%;'
            trig_by_click: '', //using "," to seperate multi targets. Default ''
            trig_by_step: true, //for landers only.  Default false
            complete: function () { //(Optional) Callback when the Ad Displays after the delay. Ad code with display method should be placed in here.

                jQuery("#" + this.id + " #ads_container").html("<div id=\"div-gpt-ad-1439387158836-0\">...</div>");
                
                var _eaq = _eaq || [];
                var a = {
                    'RenderingDiv': 'div-gpt-ad-1439387158836-0', //Id of the element which you want the Ads to render (Required)
                    'AdServer': 'DFP', //The Ad Server (Optional: defaults to DFP)
                    'Sizes': [728, 500], //The Ad Sizes which are normally added in the head (Required for Double Click Ads)
                    'AdUnitPath': '/59026966/Testing_2',  //The Ad unit Value which is normally added in the head (Required for Double Click Ads)
                    'Vendor': 'MEDIAALPHA', //The Vendor Name (Optional: VANTAGE default)
                    'IsWizard': false, //if IsWizard is true, you can add below line 
                    'AddiTargetingParam': {
                        'custom': 'testingsiderail', //Update to the value set in DFP
                    },//Customized additional targeting parameters
                };
                eddy_ad_initialize(a);
            }
        });

	});

})(jQuery);

</script>



**When rendered on the page above jQuery or Toaster Ad Scripts:

<script type="text/javascript">

defer_til_jQuery(function () {

	if(jQuery('body').hasClass('not-logged-in')){

		//Place Ad Code here.
	
	}

});

//Prevents Script From Loading until jQuery has Loaded.
function defer_til_jQuery(method) {
    if (window.jQuery && jQuery.toaster != 'undefined') {
        method();
    }
    else {
        setTimeout(function () { defer_til_jQuery(method) }, 50);
    };
}

</script>