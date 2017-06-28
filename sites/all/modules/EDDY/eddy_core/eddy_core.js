(function ($) {

    function getCookie(cname) {
        var name = cname + "=";
        var decodedCookie = decodeURIComponent(document.cookie);
        var ca = decodedCookie.split(';');
        for (var i = 0; i < ca.length; i++) {
            var c = ca[i];
            while (c.charAt(0) == ' ') {
                c = c.substring(1);
            }
            if (c.indexOf(name) == 0) {
                return c.substring(name.length, c.length);
            }
        }
        return "";
    }

    //Creates Live Method if it does not exist.
    if (typeof $.fn.live != 'function') {

        $.fn.extend({

            live: function (types, data, fn) {
                $(this.context).on(types, this.selector, data, fn);
                return this;
            },
            die: function (types, fn) { //Die is prob not a function either, they were deprecated at the same time.
                $(this.context).off(types, this.selector || "**", fn);
                return this;
            }

        });

    }
	
    //
    $.browser = {
            msie: (navigator.appName == 'Microsoft Internet Explorer')?true:false,
    };

    $.eddy_core = {

        cache_buster: {

            trackid: getCookie("_CampaignTrackID"),

            cache_qs: function () { return Drupal.settings.cache_qs },

            cache_key: function () {

                return this.trackid + "_" + this.cache_qs();

            },

            append_cache_buster_qs: function (url) {

                var output = url;

                if(url.indexOf("?") > 0){

                    output += "&";

                } else {

                    output += "?";

                }

                output += "cache_buster=" + this.cache_key();

                return output;

            }

        },

    }

})(jQuery);
