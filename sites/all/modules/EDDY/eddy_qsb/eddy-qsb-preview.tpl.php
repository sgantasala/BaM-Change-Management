<?php
/**
 * @file
 * Zen theme's implementation to display a block.
 *
 * Available variables:
 * - $title: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be "block-user".
 *   - first: The first block in the region.
 *   - last: The last block in the region.
 *   - odd: An odd-numbered block in the region's list of blocks.
 *   - even: An even-numbered block in the region's list of blocks.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see zen_preprocess_block()
 * @see template_process()
 * @see zen_process_block()
 */
$background = '';
$background_color = '';
$style_form_width = '';
$style_form_height = '';
$style_form_padding = '';
$style_form = '';
$style_background = '';

if(!empty($qsb['image_fid'])){
    $background_image = file_load($qsb['image_fid']);
    
    if(!empty($background_image)){
        $background_image_src = file_stream_wrapper_get_instance_by_uri($background_image->uri)->getDirectoryPath() . substr($background_image->uri, strpos($background_image->uri, '://')+2);
        $background = (!empty($qsb['image_fid']))? 'background:url(/' .$background_image_src . ') no-repeat;' : '';
    }
}

if(!empty($qsb['style_color'])){
    $background_color = 'background-color:' . $qsb['style_color'] . ';';
}

if(!empty($background) || !empty($background_color)){
    $style_background = 'style="' . $background . $background_color . '"';
}

if(!empty($qsb['form_width'])){
    $style_form_width = 'width:' . $qsb['form_width'] . ';';
}

if(!empty($qsb['form_height'])){
    $style_form_height = 'height:' . $qsb['form_height'] . ';';
}

if(!empty($qsb['form_padding'])){
    $style_form_padding = 'padding:' . $qsb['form_padding'] . ';';
}

if(!empty($style_form_width) || !empty($style_form_height) || !empty($style_form_padding)){
    $style_form = 'style="' . $style_form_width . $style_form_height . $style_form_padding . '"';
}
?>

<div class="qdf_style_preview <?php print $qsb['image_alignment']; ?>" <?php print $style_background; ?>">
	<div class="question-align <?php print $qsb['question_alignment'] ?> clearfix">
		<p class="block-title <?php print $qsb['title_alignment'] ?>">Your QSB Title</p>
        <div id="qdf-holder-wrapper" class="clearfix">
		    <div class="qdf-holder <?php print $qsb['form_alignment'];?>" id="<?php print $qsb['qsb_name']; ?>" <?php print $style_form; ?> >
		       <!--form class="qdf-block-form <?php //print $qsb['qsb_type']; ?>" action="<?php //print $qsb['submit_url']; ?>" method="post" target-type="<?php //print $qsb['submit_type'] ?>"-->
				    <?php if ($qsb['qsb_type'] == 'degree'){ ?>
				    <input name="cid" type="hidden" class="cid tracking-param" value="<?php print variable_get('eddy_core_global_campaign_id', ''); ?>" />
				    <!--input name="tsource" type="hidden" class="tsource tracking-param" value="test" /-->
				    <?php } ?>			
				    <ul class="qq-detail clearfix">
					    <?php   
					
						    foreach($q_question as $qq){ 
						    ?>
						    <li class="qdf-item <?php print $qq['qq_type'] . '  qq-' . $qq['sequence'] ?>">
						    <label for="<?php print $qsb['qsb_name'] . '-' . $qq['qq_type'] ?>"><?php print $qq['qq_label'] ?></label>
						    <?php 
							    switch($qq['qq_field_type']){
								    case 'dropdown':
						    ?>
								    <select id="<?php print $qq['qqid'] ?>" class="form-select qdf-<?php print $qq['qq_type'] ?>-select qdf-type-<?php print $qsb['qsb_type'] . ' ' . $qq['o_status'] ?>">
									    <option value="-1"><?php print $qq['qq_field_label'] ?></option>
								    </select>
						    <?php 
								    break; 
								    case 'textfiled';
								    break;
							    }
						    ?>
						    </li>
					    <?php 	}?>
					    <li class="submit-button <?php print $qsb['button_alignment'] ?>">
						    <input name="QDFButton" type="submit" id="QDFButton" class="form-submit <?php print $qsb['button_skin']; ?>" value="<?php print $qsb['submit_text'] ?>" />
					    </li>
				    </ul>
			    <!--/form-->
		    </div>
        </div>
	</div>
</div>
