<h3>About</h3>

<?php if($can_edit): ?>
	<ul class="action-links">
		<li>
			<?php print l('Manage EDDY Help Text', 'eddy-help'); ?> 
		</li>
	</ul>
<?php endif; ?>

<?php foreach($results as $result): ?>

	<p><strong><?php print $result->title;?></strong></p>
	<div class="content"><?php print $result->description;?></div>
	
<?php endforeach; ?>