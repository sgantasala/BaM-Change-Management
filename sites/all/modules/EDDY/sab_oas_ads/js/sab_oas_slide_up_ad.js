//Slide up ad JQuery
(function ($) {

    $(document).ready(function () {
        sitePageString = Drupal.settings.sab_oas_ads.current_site_page.replace(new RegExp('/', 'g'), '_');

        function getCookie(name) {
           
            var nameEQ = name + "=";
            var ca = document.cookie.split(';');
            for (var i = 0; i < ca.length; i++) {
                var c = ca[i];
                while (c.charAt(0) == ' ') c = c.substring(1, c.length);
                if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length, c.length);
            }
            return null;
        }

        function setCookie(name, value, days) {
       
            if (days) {
                var date = new Date();
                date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
                var expires = "; expires=" + date.toGMTString();
            } else var expires = "";
            document.cookie = name + "=" + value + expires + "; path=/";
      
        }

        function deleteCookie(name) {
            setCookie(name, "", -1);
        }

     
        if (($("#SlideUpContainer").length > 0)) {
     
            //set session cookie so that we only show the ad once per session
            var cookieC;
            //set reference to container
            var container = $("#SlideUpContainer");
            var HomeBannerAd = $("#HomeBannerAd");
            var BannerClose = $("#BannerClose");
            HomeBannerAd.hide();
            BannerClose.hide();
            container.hide();
            cookieC = getCookie(sitePageString+'sliderAdShown');
           
            if (cookieC == null) {
                //show ad container on page load if cookie doesn't exist
                container.removeAttr("style");
                container.slideDown(1500, 'linear', function () {
                
                    HomeBannerAd.fadeIn(300);
                    BannerClose.fadeIn(300);
                });
                setCookie(sitePageString + 'sliderAdShown', 'yes');

            } 

            // Bind the link to close the slider ad
            $("#closeAdvert,#closeAdvertMobile").bind('click', function () {
                // Toggle the slide based on its current
                // visibility.
                if (container.is(":visible")) {
                    // Hide - slide up.
                    HomeBannerAd.fadeOut(100);
                    BannerClose.fadeOut(100);
                    container.slideUp(500, 'linear');

                } else {
                    // Show - slide down.
                    container.slideDown(1500, 'linear', function () {
                        HomeBannerAd.fadeIn(300);
                        BannerClose.fadeIn(300)
                    });
                }
            });
        }
    });

})(jQuery);