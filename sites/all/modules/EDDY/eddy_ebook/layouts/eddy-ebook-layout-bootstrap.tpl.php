<?php
/**
 * @file
 * Eddy ebbok Bootrap Layout.
 */
?>



<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes; ?>">
 <div id="ebook-container">
     <div id="ebook-form-container" class="row col-xs-12 col-sm-12 col-md-12 clearfix">
         <div id="ebook-form-content" class="row col-xs-12 col-sm-12 col-md-6">
             <?php if ($feature_content_region): ?>
             <?php print $feature_content_region; ?>
             <?php endif; ?>
         </div>
         <div id="ebook-form" class="row col-xs-12 col-sm-12 col-md-6">
             <div class="thumbnail">
                 <div class="ebook-form-header-container clearfix">
                     <?php if ($webform_header_content_region): ?>
                     <?php print $webform_header_content_region; ?>
                     <?php endif; ?>
                 </div>
                 <div class="caption clearfix">
                     <?php if ($webform_region): ?>
                     <?php print $webform_region; ?>
                     <?php endif; ?>

                 </div>
             </div>
             <div class="ebook-form-footer-container clearfix">
                 <?php if ($webform_footer_content_region): ?>
                 <?php print $webform_footer_content_region; ?>
                 <?php endif; ?>
             </div>
         </div>
     </div>
 <div class="col-xs-12 col-sm-12 col-md-12">&nbsp;</div>
     <div id="ebook-content-container" class="row col-xs-12 col-sm-12 col-md-12">
         <?php if ($content_region): ?>
         <?php print $content_region; ?>
         <?php endif; ?>
     </div>
 </div>
</<?php print $layout_wrapper ?>>