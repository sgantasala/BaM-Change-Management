<?php
/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $caption: The caption for this table. May be empty.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */

?>

<table <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
   <?php if (!empty($title) || !empty($caption)) : ?>
     <caption><?php print $caption . $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
    <thead>
      <tr>
        <?php foreach ($header as $field => $label): ?>
          <th <?php if ($header_classes[$field]) { print 'class="'. $header_classes[$field] . '" '; } ?>>
            <?php print $label; ?>
          </th>
        <?php endforeach; ?>
      </tr>
    </thead>
  <?php endif; ?>
  <tbody>
    <?php foreach ($rows as $row_count => $row): ?>
      <tr <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  } ?>>
        <?php foreach ($row as $field => $content): ?>

          <td <?php if ($field_classes[$field][$row_count]) { print 'class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
            <?php switch($field){
                      case "status":
                      
                            $status = "";
                            switch ($content){ 
                                case "1":
                                    $status = "Approved";
                                    break;
                                case "2":
                                    $status = "Published";
                                    break;
                                case "3":
                                    $status = "Deleted";
                                    break;
                                default:
                                    $status = "Pending";
                            }
                            print $status;
                            break;

                       case "rid":

                              $operation = "";
                              
                              $operation_edit = "<a href=\"/#overlay=admin/reviews/edit/$content\" class=\"operation edit\">Edit</a>";                                  
                              $operation_approve = "<a href=\"#\" rel=\"/admin/reviews/status/$content/approve\" class=\"operation\">Approve</a>";                              
                              $operation_delete = "<a href=\"#\" rel=\"/admin/reviews/status/$content/delete\" class=\"operation\">Delete</a>";
                              $operation_publish = "<a href=\"#\" rel=\"/admin/reviews/status/$content/publish\" class=\"operation\">Publish</a>";

                              switch ($status){ 
                      
                                  case "Pending":
                                    $operation = $operation_approve;
                                    break;
                                case "Approved":
                                    $operation = $operation_publish;
                                    break;

                              }

                              print (user_access('publish reviews')) ? $operation_edit . " | " . $operation_delete . (($operation != '')? " | " . $operation : "") : "";
                              break;

                        case "created":                            
                        case "updated": 

                            print ($content == '0') ? "" : format_date($content, 'short'); 
                            break;
                        case "name":
                            if(!strpos($content, 'Anonymous')){
                                print $content;                           
                            }
                            break;
                        default:
                            print $content; 
                           break;
                  } ?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>
