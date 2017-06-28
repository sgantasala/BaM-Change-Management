(function ($) {

    $(document).ready(function () {

        //hide divs when 'empty.gif' exists which means there isn't any actual OAS add to display.

        function trackAction(sender) {
            try {
                var eventCategory = 'client';
                var eventAction = $(sender).attr('id');
                if (typeof dataLayer != 'undefined') {
                    dataLayer.push({
                        "event": "gaEvent",
                        "eventCategory": eventCategory,
                        "eventAction": eventAction
                    });
                }
                window['optimizely'] = window['optimizely'] || [];
                window.optimizely.push(["trackEvent", eventAction]);
            } catch (e) { }
        }

        if ($("#OAS_Position1").html() != null) {
            if ($("#OAS_Position1").html().indexOf('empty.gif') > -1) {
                $("#OAS_Position1").detach();
                $("#Hidden_OAS_Position1").detach();
                //$("#SlideUpContainer").detach();
            } else {
                $('#OAS_Position1').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x50").html() != null) {
            if ($("#Hidden_OAS_x50").html().indexOf('empty.gif') > -1) {
                $("#OAS_x50").detach();
                $("#Hidden_OAS_x50").detach();
            } else {
                $('#OAS_x50').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x51").html() != null) {
            if ($("#OAS_x51").html().indexOf('empty.gif') > -1) {
                $("#OAS_x51").detach();
                $("#Hidden_OAS_x51").detach();
            } else {
                $('#OAS_x51').click(function () {
                    trackAction(this);
                });
            }
        };


        if ($("#OAS_x52").html() != null) {
            if ($("#OAS_x52").html().indexOf('empty.gif') > -1) {
                $("#OAS_x52").detach();
                $("#Hidden_OAS_x52").detach();
            } else {
                $('#OAS_x52').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x53").html() != null) {
            if ($("#OAS_x53").html().indexOf('empty.gif') > -1) {
                $("#OAS_x53").detach();
                $("#Hidden_OAS_x53").detach();
            } else {
                $('#OAS_x53').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x55").html() != null) {
            if ($("#OAS_x55").html().indexOf('empty.gif') > -1) {
                $("#OAS_x55").detach();
                $("#Hidden_OAS_x55").detach();
            } else {
                $('#OAS_x55').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x56").html() != null) {
            if ($("#OAS_x56").html().indexOf('empty.gif') > -1) {
                $("#OAS_x56").detach();
                $("#Hidden_OAS_x56").detach();
            } else {
                $('#OAS_x56').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x62").html() != null) {
            if ($("#OAS_x62").html().indexOf('empty.gif') > -1) {
                $("#OAS_x62").detach();
                $("#Hidden_OAS_x62").detach();
            } else {
                $('#OAS_x62').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x63").html() != null) {
            if ($("#OAS_x63").html().indexOf('empty.gif') > -1) {
                $("#OAS_x63").detach();
                $("#Hidden_OAS_x63").detach();
            } else {
                $('#OAS_x63').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x64").html() != null) {
            if ($("#OAS_x64").html().indexOf('empty.gif') > -1) {
                $("#OAS_x64").detach();
                $("#Hidden_OAS_x64").detach();
            } else {
                $('#OAS_x64').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x65").html() != null) {
            if ($("#OAS_x65").html().indexOf('empty.gif') > -1) {
                $("#OAS_x65").detach();
                $("#Hidden_OAS_x65").detach();
            } else {
                $('#OAS_x65').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x66").html() != null) {
            if ($("#OAS_x66").html().indexOf('empty.gif') > -1) {
                $("#OAS_x66").detach();
                $("#Hidden_OAS_x66").detach();
            } else {
                $('#OAS_x66').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x67").html() != null) {
            if ($("#OAS_x67").html().indexOf('empty.gif') > -1) {
                $("#OAS_x67").detach();
                $("#Hidden_OAS_x67").detach();
            } else {
                $('#OAS_x67').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x68").html() != null) {
            if ($("#OAS_x68").html().indexOf('empty.gif') > -1) {
                $("#OAS_x68").detach();
                $("#Hidden_OAS_x68").detach();
            } else {

                $('#OAS_x68').click(function () {
                    trackAction(this);
           
                });
            }
        };

        if ($("#OAS_x69").html() != null) {
            if ($("#OAS_x69").html().indexOf('empty.gif') > -1) {
                $("#OAS_x69").detach();
                $("#Hidden_OAS_x69").detach();
            } else {
                $('#OAS_x69').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x77").html() != null) {
            if ($("#OAS_x77").html().indexOf('empty.gif') > -1) {
                $("#OAS_x77").detach();
                $("#Hidden_OAS_x77").detach();
            } else {
                $('#OAS_x77').click(function () {
                    trackAction(this);
                });
            }
        };


        if ($("#OAS_x81").html() != null) {
            if ($("#OAS_x81").html().indexOf('empty.gif') > -1) {
                $("#OAS_x81").detach();
                $("#Hidden_OAS_x81").detach();
            } else {
                $('#OAS_x81').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x82").html() != null) {
            if ($("#OAS_x82").html().indexOf('empty.gif') > -1) {
                $("#OAS_x82").detach();
                $("#Hidden_OAS_x82").detach();
            } else {
                $('#OAS_x82').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x84").html() != null) {
            if ($("#OAS_x84").html().indexOf('empty.gif') > -1) {
                $("#OAS_x84").detach();
                $("#Hidden_OAS_x84").detach();
            } else {
                $('#OAS_x84').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x85").html() != null) {
            if ($("#OAS_x85").html().indexOf('empty.gif') > -1) {
                $("#OAS_x85").detach();
                $("#Hidden_OAS_x85").detach();
            } else {
                $('#OAS_x85').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x86").html() != null) {
            if ($("#OAS_x86").html().indexOf('empty.gif') > -1) {
                $("#OAS_x86").detach();
                $("#Hidden_OAS_x86").detach();
            } else {
                $('#OAS_x86').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x88").html() != null) {
            if ($("#OAS_x88").html().indexOf('empty.gif') > -1) {
                $("#OAS_x88").detach();
                $("#Hidden_OAS_x88").detach();
            } else {
                $('#OAS_x88').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x91").html() != null) {
            if ($("#OAS_x91").html().indexOf('empty.gif') > -1) {
                $("#OAS_x91").detach();
                $("#Hidden_OAS_x91").detach();
            } else {
                $('#OAS_x91').click(function () {
                    trackAction(this);
                });
            }
        };
        if ($("#OAS_x92").html() != null) {
            if ($("#OAS_x92").html().indexOf('empty.gif') > -1) {
                $("#OAS_x92").detach();
                $("#Hidden_OAS_x92").detach();
            } else {
                $('#OAS_x92').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x93").html() != null) {
            if ($("#OAS_x93").html().indexOf('empty.gif') > -1) {
                $("#OAS_x93").detach();
                $("#Hidden_OAS_x93").detach();
            } else {
                $('#OAS_x93').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x94").html() != null) {
            if ($("#OAS_x94").html().indexOf('empty.gif') > -1) {
                $("#OAS_x94").detach();
                $("#Hidden_OAS_x94").detach();
            } else {
                $('#OAS_x94').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x95").html() != null) {
            if ($("#OAS_x95").html().indexOf('empty.gif') > -1) {
                $("#OAS_x95").detach();
                $("#Hidden_OAS_x95").detach();
            } else {
                $('#OAS_x95').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x96").html() != null) {
            if ($("#OAS_x96").html().indexOf('empty.gif') > -1) {
                $("#OAS_x96").detach();
                $("#Hidden_OAS_x96").detach();
            } else {
                $('#OAS_x96').click(function () {
                    trackAction(this);
                });
            }
        };

        if ($("#OAS_x88").html() != null) {
            if ($("#OAS_x88").html().indexOf('empty.gif') > -1) {
                $("#OAS_x88").detach();
                $("#Hidden_OAS_x88").detach();
            } else {
                $('#OAS_x88').click(function () {
                    trackAction(this);
                });
            }
        };


    });

})(jQuery);