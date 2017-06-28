<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>

<?php print $wrapper_prefix; ?>
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>  
  <?php foreach ($rows as $id => $row): ?>
  <?php   if($id == 0 || $id == 2): ?>
          <div class="column-div">
          <?php print $list_type_prefix; ?>
  <?php endif; ?>
            <li class="<?php print $classes_array[$id]; ?>"><?php print $row; ?></li>
  <?php   if($id == 1 || $id == 3): ?>

          <?php print $list_type_suffix; ?>
          </div>
  <?php endif; ?>
  <?php endforeach; ?>
<?php print $wrapper_suffix; ?>
