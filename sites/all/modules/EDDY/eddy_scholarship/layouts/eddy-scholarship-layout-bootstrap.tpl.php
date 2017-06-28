<?php
/**
 * @file
 * Eddy scholarship contest Bootrap Layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes; ?>">

<div class="scholarship-container">
    <div class="col-md-12 scholarship-header-image hidden-sm hidden-xs"></div>
    <div class="scholarship-form-container clearfix">

        <div class="col-md-6 header-image hidden-sm hidden-xs">
            <div class="scholarship-page-title">
              <?php if ($webform_title): ?>
              <?php print $webform_title; ?>
              <?php endif; ?>
            </div>
        </div>
        <div class="col-md-6">
            <div class="thumbnail">
                <div class="caption">
                    <div class="row scholarship-form-header-container">
                        <?php if ($webform_header_content_region): ?>
                        <?php print $webform_header_content_region; ?>
                        <?php endif; ?>
                    </div>
                    <div id="scholarship-form">
                        <?php if ($webform_region): ?>
                        <?php print $webform_region; ?>
                        <?php endif; ?>
                    </div>
                    <div class="row scholarship-form-footer-container">
                        <?php if ($webform_footer_content_region): ?>
                        <?php print $webform_footer_content_region; ?>
                        <?php endif; ?>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <div class="col-xs-12 col-sm-12 col-md-12 clearfix">
        <?php if ($content_region): ?>
        <?php print $content_region; ?>
        <?php endif; ?>
    </div>

   
</div>
</<?php print $layout_wrapper ?>>