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

$style_form_width = '';
$style_form_height = '';
$style_form_padding = '';
$style_form = '';
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
    $style_form = 'style="' . $style_form_width . $style_form_height  . $style_form_padding . '"';
}

?>

 <div id="qdf-holder-wrapper" class="clearfix">
	<div class="qdf-holder <?php print $qsb['form_alignment']; ?>" id="<?php print $qsb['qsb_name']; ?>" <?php print $style_form; ?> >
	   <form class="qdf-block-form <?php print $qsb['qsb_type']; ?>" action="<?php print $qsb['submit_url']; ?>" method="post" target-type="<?php print $qsb['submit_type'] ?>">
			<input name="qsb_type" type="hidden" class="qsb_type" value="<?php print $qsb['qsb_type'] ?>" />
			
			<?php if ($qsb['qsb_type'] == EDDY_QSB_TYPE_DEGREE){ ?>
			<input name="submit_type" type="hidden" class="submit_type" value="<?php print $qsb['submit_type'] ?>" />
			<input name="form_url" type="hidden" class="form_url" value="<?php print $qsb['submit_url']; ?>" />
			<input name="cid" type="hidden" class="cid tracking-param" value="<?php print variable_get('eddy_core_global_campaign_id', ''); ?>" />
			<!--input name="tsource" type="hidden" class="tsource tracking-param" value="test" /-->						
			<?php } 
				if (!empty($q_question)){
			?>
					<ul class="qq-detail clearfix">
						<?php   
								foreach($q_question as $qq){ 
								?>
								<li class="<?php print $qq['qq_type'] . ' qsb-question  qq-' . $qq['sequence'] ?>">
								<label for="<?php print $qsb['qsb_name'] . '-' . $qq['qq_type'] ?>"><?php print $qq['qq_label'] ?></label>
								<?php 
									switch($qq['qq_field_type']){
										case 'dropdown':
								?>
										<select id="<?php print $qq['qqid'] ?>" name="qdf-<?php print $qq['qq_type'] ?>-select" class="qdf-block-form-item qdf-<?php print $qq['qq_type'] ?>-select qdf-type-<?php print $qsb['qsb_type'] . ' ' . $qq['o_status'] ?>">
											<option value="-1"><?php print $qq['qq_field_label'] ?></option>
										</select>
								<?php 
										break; 
										case 'textfiled';
										break;
									}
								?>
								</li>
						<?php } ?>
						<li class="submit-button">
							<input name="QDFButton" type="submit" id="QDFButton" class="form-submit <?php print $qsb['button_skin']; ?>" value="<?php print $qsb['submit_text'] ?>" />
						</li>
					</ul>
			<?php
				}
			?>
		</form>
	</div>
</div>
