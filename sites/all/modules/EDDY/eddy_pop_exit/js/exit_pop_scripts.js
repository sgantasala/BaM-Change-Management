function dfp_display_pop_up(divID,VendorID) {

    if (typeof eddy_ad_initialize == 'function') {

        jQuery("document").ready(function () {

            var v = {};

            v.Vendor = VendorID;
            v.AdServer = 'DFP';
            v.RenderingDiv = divID;

            eddy_ad_initialize(v);

        });

    }

}