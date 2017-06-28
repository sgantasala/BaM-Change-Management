<?php
    $edit = '<span class="edit-widget label label-default"><i class="glyphicon glyphicon-edit"></i> edit</span>';
?>
<div class="sidebar-nav">
    <ul class="nav nav-list accordion-group">
        <li class="nav-header">
            <div class="pull-right popover-info">
                <i class="glyphicon glyphicon-question-sign"></i>
                <div class="popover fade right">
                    <div class="arrow"></div>
                    <h3 class="popover-title">Help</h3>
                    <div class="popover-content">
                        To change the column configuration you can edit the different values in the input (they should add 12). If you need more info please visit
                        <a target="_blank" href="http://getbootstrap.com/css/#grid">Bootstrap grid system.</a>
                    </div>
                </div>
            </div>
            <i class="glyphicon-plus glyphicon"></i>
            Grid system
        </li>
        <li class="rows" id="estRows">
            <div class="lyrow ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon-remove glyphicon"></i>
                    remove
                </a>
                <span class="drag label label-default  ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">
                    <input type="text" value="12" placeholder="Enter your own" class="form-control" />
                </div>
                <div class="view">
                    <div class="row">
                        <div class="col-md-12 column"></div>
                    </div>
                </div>
            </div>
            <div class="lyrow ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon-remove glyphicon"></i>
                    remove
                </a>
                <span class="drag label label-default  ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">
                    <input type="text" value="6 6" placeholder="Enter your own" class="form-control" />
                </div>
                <div class="view">
                    <div class="row">
                        <div class="col-md-6 column"></div>
                        <div class="col-md-6 column"></div>
                    </div>
                </div>
            </div>
            <div class="lyrow ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon-remove glyphicon"></i>
                    remove
                </a>
                <span class="drag label label-default  ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">
                    <input type="text" value="8 4" placeholder="Enter your own" class="form-control" />
                </div>
                <div class="view">
                    <div class="row">
                        <div class="col-md-8 column"></div>
                        <div class="col-md-4 column"></div>
                    </div>
                </div>
            </div>
            <div class="lyrow ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon-remove glyphicon"></i>
                    remove
                </a>
                <span class="drag label label-default  ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">
                    <input type="text" value="4 4 4" placeholder="Enter your own" class="form-control" />
                </div>
                <div class="view">
                    <div class="row">
                        <div class="col-md-4 column"></div>
                        <div class="col-md-4 column"></div>
                        <div class="col-md-4 column"></div>
                    </div>
                </div>
            </div>
            <div class="lyrow ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon-remove glyphicon"></i>
                    remove
                </a>
                <span class="drag label label-default display-none ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">
                    <input type="text" value="" placeholder="Enter your own" class="form-control" />
                </div>
                <div class="view">
                    <div class="row"></div>
                </div>
            </div>
        </li>
    </ul>

    <ul class="nav nav-list accordion-group">
        <li class="nav-header">
            <i class="glyphicon glyphicon-plus"></i>
            Base CSS
            <div class="pull-right popover-info">
                <i class="glyphicon glyphicon-question-sign "></i>
                <div class="popover fade right">
                    <div class="arrow"></div>
                    <h3 class="popover-title">Help</h3>
                    <div class="popover-content">
                        Drag &amp; Drop the elements inside the columns where you want to insert it. And from there, you can configure the style of that element. If you need more info please visit
                        <a target="_blank" href="http://getbootstrap.com/css">Base CSS.</a>
                    </div>
                </div>
            </div>
        </li>
        <li class="boxes" id="elmBase">
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Align
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="active">
                                <a href="#" rel="">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-left">Left</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-center">Center</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-right">Right</a>
                            </li>
                        </ul>
                    </span>
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Emphasis
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="active">
                                <a href="#" rel="">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-muted">Muted</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-primary">Primary</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-success">Success</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-info">Info</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-warning">Warning</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-danger">Danger</a>
                            </li>
                        </ul>
                    </span>
                </span>
                <div class="preview">Title</div>
                <div class="view">
                    <h3 contenteditable="true">h3. Lorem ipsum dolor sit amet.</h3>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Align
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="active">
                                <a href="#" rel="">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-left">Left</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-center">Center</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-right">Right</a>
                            </li>
                        </ul>
                    </span>
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Emphasis
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="active">
                                <a href="#" rel="">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-muted">Muted</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-primary">Primary</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-success">Success</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-info">Info</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-warning">Warning</a>
                            </li>
                            <li class="">
                                <a href="#" rel="text-danger">Danger</a>
                            </li>
                        </ul>
                    </span>

                    <a class="btn btn-xs btn-default" href="#" rel="lead">Lead</a>
                </span>
                <div class="preview">Paragraph</div>
                <div class="view">
                    <p contenteditable="true">
                        Lorem ipsum dolor sit amet,
                        <strong>consectetur adipiscing elit</strong>
                        . Aliquam eget sapien sapien. Curabitur in metus urna. In hac habitasse platea dictumst. Phasellus eu sem sapien, sed vestibulum velit. Nam purus nibh, lacinia non faucibus et, pharetra in dolor. Sed iaculis posuere diam ut cursus.
                        <em>Morbi commodo sodales nisi id sodales. Proin consectetur, nisi id commodo imperdiet, metus nunc consequat lectus, id bibendum diam velit et dui.</em>
                        Proin massa magna, vulputate nec bibendum nec, posuere nec lacus.
                        <small>Aliquam mi erat, aliquam vel luctus eu, pharetra quis elit. Nulla euismod ultrices massa, et feugiat ipsum consequat eu. </small>
                    </p>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">Address</div>
                <div class="view">
                    <address contenteditable="true">
                        <strong>Twitter, Inc.</strong>
                        <br />
                        795 Folsom Ave, Suite 600
                        <br />
                        San Francisco, CA 94107
                        <br />
                        <abbr title="Phone">P:</abbr>
                        (123) 456-7890
                    </address>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <a class="btn btn-xs btn-default" href="#" rel="pull-right">Pull right</a>
                </span>
                <div class="preview">Blockquote</div>
                <div class="view">
                    <blockquote contenteditable="true">
                        <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer posuere erat a ante.</p>
                        <small>
                            Someone famous
                            <cite title="Source Title">Source Title</cite>
                        </small>
                    </blockquote>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <a class="btn btn-xs btn-default" href="#" rel="list-unstyled">Unstyled</a>
                    <a class="btn btn-xs btn-default" href="#" rel="list-inline">Inline</a>
                </span>
                <div class="preview">Unordered List</div>
                <div class="view">
                    <ul contenteditable="true">
                        <li>Lorem ipsum dolor sit amet</li>
                        <li>Consectetur adipiscing elit</li>
                        <li>Integer molestie lorem at massa</li>
                        <li>Facilisis in pretium nisl aliquet</li>
                        <li>Nulla volutpat aliquam velit</li>
                        <li>Faucibus porta lacus fringilla vel</li>
                        <li>Aenean sit amet erat nunc</li>
                        <li>Eget porttitor lorem</li>
                    </ul>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <a class="btn btn-xs btn-default" href="#" rel="list-unstyled">Unstyled</a>
                    <a class="btn btn-xs btn-default" href="#" rel="list-inline">Inline</a>
                </span>
                <div class="preview">Ordered List</div>
                <div class="view">
                    <ol contenteditable="true">
                        <li>Lorem ipsum dolor sit amet</li>
                        <li>Consectetur adipiscing elit</li>
                        <li>Integer molestie lorem at massa</li>
                        <li>Facilisis in pretium nisl aliquet</li>
                        <li>Nulla volutpat aliquam velit</li>
                        <li>Faucibus porta lacus fringilla vel</li>
                        <li>Aenean sit amet erat nunc</li>
                        <li>Eget porttitor lorem</li>
                    </ol>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <a class="btn btn-xs btn-default" href="#" rel="dl-horizontal">Horizontal</a>
                </span>
                <div class="preview">Description</div>
                <div class="view">
                    <dl contenteditable="true">
                        <dt>Description lists</dt>
                        <dd>A description list is perfect for defining terms.</dd>
                        <dt>Euismod</dt>
                        <dd>Vestibulum id ligula porta felis euismod semper eget lacinia odio sem nec elit.</dd>
                        <dd>Donec id elit non mi porta gravida at eget metus.</dd>
                        <dt>Malesuada porta</dt>
                        <dd>Etiam porta sem malesuada magna mollis euismod.</dd>
                        <dt>Felis euismod semper eget lacinia</dt>
                        <dd>Fusce dapibus, tellus ac cursus commodo, tortor mauris condimentum nibh, ut fermentum massa justo sit amet risus.</dd>
                    </dl>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Style
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="active">
                                <a href="#" rel="">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="table-striped">Striped</a>
                            </li>
                            <li class="">
                                <a href="#" rel="table-bordered">Bordered</a>
                            </li>
                        </ul>
                    </span>
                    <a class="btn btn-xs btn-default" href="#" rel="table-hover">Hover</a>
                    <a class="btn btn-xs btn-default" href="#" rel="table-condensed">Condensed</a>
                </span>
                <div class="preview">Table</div>
                <div class="view">
                    <table class="table" contenteditable="true">
                        <thead>
                            <tr>
                                <th>#</th>
                                <th>Product</th>
                                <th>Payment Taken</th>
                                <th>Status</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr>
                                <td>1</td>
                                <td>TB - Monthly</td>
                                <td>01/04/2012</td>
                                <td>Default</td>
                            </tr>
                            <tr class="active">
                                <td>1</td>
                                <td>TB - Monthly</td>
                                <td>01/04/2012</td>
                                <td>Approved</td>
                            </tr>
                            <tr class="success">
                                <td>2</td>
                                <td>TB - Monthly</td>
                                <td>02/04/2012</td>
                                <td>Declined</td>
                            </tr>
                            <tr class="warning">
                                <td>3</td>
                                <td>TB - Monthly</td>
                                <td>03/04/2012</td>
                                <td>Pending</td>
                            </tr>
                            <tr class="danger">
                                <td>4</td>
                                <td>TB - Monthly</td>
                                <td>04/04/2012</td>
                                <td>Call in to confirm</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Styles
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="">
                                <a href="#" rel="btn-default">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-primary">Primary</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-success">Success</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-info">Info</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-warning">Warning</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-danger">Danger</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-link">Link</a>
                            </li>
                        </ul>
                    </span>
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Size
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="">
                                <a href="#" rel="btn-lg">Large</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-default">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-sm">Small</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-xs">Mini</a>
                            </li>
                        </ul>
                    </span>

                    <a class="btn btn-xs btn-default" href="#" rel="btn-block">Block</a>
                    <a class="btn btn-xs btn-default" href="#" rel="active">Active</a>
                    <a class="btn btn-xs btn-default" href="#" rel="disabled">Disabled</a>
                </span>
                <div class="preview">Button</div>
                <div class="view">
                    <button type="button" class="btn btn-default" contenteditable="true">Default</button>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Styles
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="">
                                <a href="#" rel="btn-default">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-primary">Primary</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-success">Success</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-info">Info</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-warning">Warning</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-danger">Danger</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-link">Link</a>
                            </li>
                        </ul>
                    </span>
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Size
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="">
                                <a href="#" rel="btn-lg">Large</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-default">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-sm">Small</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-xs">Mini</a>
                            </li>
                        </ul>
                    </span>

                    <a class="btn btn-xs btn-default" href="#" rel="btn-block">Block</a>
                    <a class="btn btn-xs btn-default" href="#" rel="active">Active</a>
                    <a class="btn btn-xs btn-default" href="#" rel="disabled">Disabled</a>
                </span>
                <div class="preview">Anchor Button</div>
                <div class="view">
                    <a href="#" class="btn" type="button" contenteditable="true">Button</a>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Styles
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="active">
                                <a href="#" rel="">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="img-rounded">Rounded</a>
                            </li>
                            <li class="">
                                <a href="#" rel="img-circle">Circle</a>
                            </li>
                            <li class="">
                                <a href="#" rel="img-thumbnail">Thumbnail</a>
                            </li>
                        </ul>
                    </span>
                </span>
                <div class="preview">Image</div>
                <div class="view">
                    <img alt="Bootstrap Image Preview" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/saved_resource.jpg" />
                </div>
            </div>
        </li>
    </ul>
    <ul class="nav nav-list accordion-group">
        <li class="nav-header">
            <i class="glyphicon glyphicon-plus"></i>
            Components
            <div class="pull-right popover-info">
                <i class="glyphicon glyphicon-question-sign "></i>
                <div class="popover fade right">
                    <div class="arrow"></div>
                    <h3 class="popover-title">Help</h3>
                    <div class="popover-content">
                        Drag &amp; Drop the elements inside the columns where you want to insert it. And from there, you can configure the style of that component. If you need more info please visit
                        <a target="_blank" href="http://getbootstrap.com/components">Components.</a>
                    </div>
                </div>
            </div>
        </li>
        <li class="boxes" id="elmComponents">

            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">Carousel</div>
                <div class="view">


                    <div class="carousel slide" id="myCarousel">
                        <ol class="carousel-indicators">
                            <li class="active" data-slide-to="0" data-target="#myCarousel"></li>
                            <li data-slide-to="1" data-target="#myCarousel" class=""></li>
                            <li data-slide-to="2" data-target="#myCarousel" class=""></li>
                        </ol>
                        <div class="carousel-inner">
                            <div class="item active">
                                <img alt="Carousel Bootstrap First" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/sports-q-c-1600-500-1.jpg" />
                                <div class="carousel-caption">
                                    <h4>First Thumbnail label</h4>
                                    <p>Cras justo odio, dapibus ac facilisis in, egestas eget quam. Donec id elit non mi porta gravida at eget metus. Nullam id dolor id nibh ultricies vehicula ut id elit.</p>
                                </div>
                            </div>
                            <div class="item">
                                <img alt="Carousel Bootstrap Second" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/sports-q-c-1600-500-2.jpg" />
                                <div class="carousel-caption">
                                    <h4>Second Thumbnail label</h4>
                                    <p>Cras justo odio, dapibus ac facilisis in, egestas eget quam. Donec id elit non mi porta gravida at eget metus. Nullam id dolor id nibh ultricies vehicula ut id elit.</p>
                                </div>
                            </div>
                            <div class="item">
                                <img alt="Carousel Bootstrap Third" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/sports-q-c-1600-500-3.jpg" />
                                <div class="carousel-caption">
                                    <h4>Third Thumbnail label</h4>
                                    <p>Cras justo odio, dapibus ac facilisis in, egestas eget quam. Donec id elit non mi porta gravida at eget metus. Nullam id dolor id nibh ultricies vehicula ut id elit.</p>
                                </div>
                            </div>
                        </div>
                        <a class="left carousel-control" href="#myCarousel" data-slide="prev">
                            <span class="glyphicon glyphicon-chevron-left"></span>
                        </a>
                        <a class="right carousel-control" href="#myCarousel" data-slide="next">
                            <span class="glyphicon glyphicon-chevron-right"></span>
                        </a>
                    </div>
                </div>
            </div>

            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Size
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="active">
                                <a href="#" rel="">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-group-lg">Large</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-group-md">Medium</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-group-sm">Small</a>
                            </li>
                            <li class="">
                                <a href="#" rel="btn-group-xs">Extra small</a>
                            </li>
                        </ul>
                    </span>
                    <a class="btn btn-xs btn-default" href="#" rel="btn-group-vertical">Vertical</a>
                </span>
                <div class="preview">Button Group</div>
                <div class="view">
                    <div class="btn-group">
                        <button class="btn btn-default" type="button">
                            <i class="glyphicon glyphicon-align-left"></i>
                            Left
                        </button>
                        <button class="btn btn-default" type="button">
                            <i class="glyphicon glyphicon-align-center"></i>
                            Center
                        </button>
                        <button class="btn btn-default" type="button">
                            <i class="glyphicon glyphicon-align-right"></i>
                            Right
                        </button>
                        <button class="btn btn-default" type="button">
                            <i class="glyphicon glyphicon-align-justify"></i>
                            Justify
                        </button>
                    </div>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <a class="btn btn-xs btn-default" href="#" rel="dropup">Dropup</a>
                </span>
                <div class="preview">Button Dropdowns</div>
                <div class="view">
                    <div class="btn-group">
                        <button class="btn btn-default" contenteditable="true">Action</button>
                        <button data-toggle="dropdown" class="btn btn-default dropdown-toggle">
                            <span class="caret"></span>
                        </button>
                        <ul class="dropdown-menu" contenteditable="true">
                            <li>
                                <a href="#">Action</a>
                            </li>
                            <li class="disabled">
                                <a href="#">Another action</a>
                            </li>
                            <li class="divider"></li>
                            <li>
                                <a href="#">Something else here</a>
                            </li>
                        </ul>
                    </div>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Styles
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="">
                                <a href="#" rel="nav-tabs">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="nav-pills">Pills</a>
                            </li>
                        </ul>
                    </span>
                    <a class="btn btn-xs btn-default" href="#" rel="nav-stacked">Stacked</a>
                </span>
                <div class="preview">Navs</div>
                <div class="view">
                    <ul class="nav nav-tabs" contenteditable="true">
                        <li class="active">
                            <a href="#">Home</a>
                        </li>
                        <li>
                            <a href="#">Profile</a>
                        </li>
                        <li class="disabled">
                            <a href="#">Messages</a>
                        </li>
                        <li class="dropdown pull-right">
                            <a href="#" data-toggle="dropdown" class="dropdown-toggle">
                                Dropdown
                                <b class="caret"></b>
                            </a>
                            <ul class="dropdown-menu">
                                <li>
                                    <a href="#">Action</a>
                                </li>
                                <li>
                                    <a href="#">Another action</a>
                                </li>
                                <li>
                                    <a href="#">Something else here</a>
                                </li>
                                <li class="divider"></li>
                                <li>
                                    <a href="#">Separated link</a>
                                </li>
                            </ul>
                        </li>
                    </ul>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">Breadcrumb</div>
                <div class="view">
                    <ul class="breadcrumb">
                        <li>
                            <a href="#" contenteditable="true">Home</a>
                            <span class="divider">/</span>
                        </li>
                        <li>
                            <a href="#" contenteditable="true">Library</a>
                            <span class="divider">/</span>
                        </li>
                        <li class="active" contenteditable="true">Data</li>
                    </ul>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Size
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="">
                                <a href="#" rel="pagination-lg">Large</a>
                            </li>
                            <li class="active">
                                <a href="#" rel="">Medium</a>
                            </li>
                            <li class="">
                                <a href="#" rel="pagination-sm">Small</a>
                            </li>
                        </ul>
                    </span>
                </span>
                <div class="preview">Pagination</div>
                <div class="view">
                    <ul class="pagination" contenteditable="true">
                        <li>
                            <a href="#">Prev</a>
                        </li>
                        <li>
                            <a href="#">1</a>
                        </li>
                        <li>
                            <a href="#">2</a>
                        </li>
                        <li>
                            <a href="#">3</a>
                        </li>
                        <li>
                            <a href="#">4</a>
                        </li>
                        <li>
                            <a href="#">5</a>
                        </li>
                        <li>
                            <a href="#">Next</a>
                        </li>
                    </ul>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Styles
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="">
                                <a href="#" rel="label-default">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="label-primary">Primary</a>
                            </li>
                            <li class="">
                                <a href="#" rel="label-success">Success</a>
                            </li>
                            <li class="">
                                <a href="#" rel="label-info">Info</a>
                            </li>
                            <li class="">
                                <a href="#" rel="label-warning">Warning</a>
                            </li>
                            <li class="">
                                <a href="#" rel="label-danger">Danger</a>
                            </li>
                        </ul>
                    </span>
                </span>
                <div class="preview">Label</div>
                <div class="view">
                    <span class="label label-default" contenteditable="true">Label</span>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration"></span>
                <div class="preview">Badge</div>
                <div class="view">
                    <ul class="nav nav-pills" contenteditable="true">
                        <li class="active">
                            <a href="#">
                                <span class="badge pull-right">42</span>
                                Home
                            </a>
                        </li>
                        <li>
                            <a href="#">
                                <span class="badge pull-right">16</span>
                                More
                            </a>
                        </li>
                    </ul>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <a class="btn btn-xs btn-default" href="#" rel="well">Well</a>
                </span>
                <div class="preview">Jumbotron</div>
                <div class="view">
                    <div class="jumbotron" contenteditable="true">
                        <h2>Hello, world!</h2>
                        <p>This is a template for a simple marketing or informational website. It includes a large callout called the hero unit and three supporting pieces of content. Use it as a starting point to create something more unique.</p>
                        <p>
                            <a class="btn btn-primary btn-large" href="#">Learn more</a>
                        </p>
                    </div>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">Page Header</div>
                <div class="view">
                    <div class="page-header">
                        <h1 contenteditable="true">
                            LayoutIt!
                            <small>Interface Builder for Bootstrap</small>
                        </h1>
                    </div>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">Text</div>
                <div class="view">
                    <h2 contenteditable="true">Heading</h2>
                    <p contenteditable="true">Donec id elit non mi porta gravida at eget metus. Fusce dapibus, tellus ac cursus commodo, tortor mauris condimentum nibh, ut fermentum massa justo sit amet risus. Etiam porta sem malesuada magna mollis euismod. Donec sed odio dui.</p>
                    <p>
                        <a class="btn" href="#" contenteditable="true">View details &raquo;</a>
                    </p>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">Thumbnails</div>
                <div class="view">
                    <div class="row">
                        <div class="col-md-4">
                            <div class="thumbnail">
                                <img alt="Bootstrap Thumbnail First" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/people-q-c-600-200-1.jpg" />
                                <div class="caption" contenteditable="true">
                                    <h3>Thumbnail label</h3>
                                    <p>Cras justo odio, dapibus ac facilisis in, egestas eget quam. Donec id elit non mi porta gravida at eget metus. Nullam id dolor id nibh ultricies vehicula ut id elit.</p>
                                    <p>
                                        <a class="btn btn-primary" href="#">Action</a>
                                        <a class="btn" href="#">Action</a>
                                    </p>
                                </div>
                            </div>
                        </div>
                        <div class="col-md-4">
                            <div class="thumbnail">
                                <img alt="Bootstrap Thumbnail Second" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/city-q-c-600-200-1.jpg" />
                                <div class="caption" contenteditable="true">
                                    <h3>Thumbnail label</h3>
                                    <p>Cras justo odio, dapibus ac facilisis in, egestas eget quam. Donec id elit non mi porta gravida at eget metus. Nullam id dolor id nibh ultricies vehicula ut id elit.</p>
                                    <p>
                                        <a class="btn btn-primary" href="#">Action</a>
                                        <a class="btn" href="#">Action</a>
                                    </p>
                                </div>
                            </div>
                        </div>
                        <div class="col-md-4">
                            <div class="thumbnail">
                                <img alt="Bootstrap Thumbnail Third" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/sports-q-c-600-200-1.jpg" />
                                <div class="caption" contenteditable="true">
                                    <h3>Thumbnail label</h3>
                                    <p>Cras justo odio, dapibus ac facilisis in, egestas eget quam. Donec id elit non mi porta gravida at eget metus. Nullam id dolor id nibh ultricies vehicula ut id elit.</p>
                                    <p>
                                        <a class="btn btn-primary" href="#">Action</a>
                                        <a class="btn" href="#">Action</a>
                                    </p>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <?php /*
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger"><i class="glyphicon glyphicon-remove"></i> remove</a>
                <span class="drag label label-default ui-draggable-handle"><i class="glyphicon glyphicon-move"></i> drag</span>
                <?php print $edit; ?>
                <span class="configuration">
                    <a class="btn btn-xs btn-default" href="#" rel="progress-striped">Striped</a>
                    <a class="btn btn-xs btn-default" href="#" rel="active">Active</a>
                </span>
                <div class="preview">Progress Bar</div>
                <div class="view">
                    <div class="progress">
                        <div class="progress-bar progress-success" style="width: 60%;"></div>
                    </div>
                </div>
            </div>
            */ ?>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <a class="btn btn-xs btn-default" href="#" rel="well">well</a>
                </span>
                <div class="preview">Media Object</div>
                <div class="view">
                    <div class="media">
                        <a href="#" class="pull-left">
                            <img alt="Bootstrap Media Preview" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/saved_resource(1).jpg" class="media-object" />
                        </a>
                        <div class="media-body" contenteditable="true">
                            <h4 class="media-heading">Nested media heading</h4>
                            Cras sit amet nibh libero, in gravida nulla. Nulla vel metus scelerisque ante sollicitudin commodo. Cras purus odio, vestibulum in vulputate at, tempus viverra turpis.
                            <div class="media">
                                <a href="#" class="pull-left">
                                    <img alt="Bootstrap Media Another Preview" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/saved_resource(1).jpg" class="media-object" />
                                </a>
                                <div class="media-body" contenteditable="true">
                                    <h4 class="media-heading">Nested media heading</h4>
                                    Cras sit amet nibh libero, in gravida nulla. Nulla vel metus scelerisque ante sollicitudin commodo. Cras purus odio, vestibulum in vulputate at, tempus viverra turpis.
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration"></span>
                <div class="preview">List group</div>
                <div class="view">
                    <div class="list-group" contenteditable="true">
                        <a href="#" class="list-group-item active">Home</a>
                        <div class="list-group-item">List header</div>
                        <div class="list-group-item">
                            <h4 class="list-group-item-heading">List group item heading</h4>
                            <p class="list-group-item-text">...</p>
                        </div>
                        <div class="list-group-item">
                            <span class="badge">14</span>
                            Help
                        </div>
                        <a class="list-group-item active">
                            <span class="badge">14</span>
                            Help
                        </a>
                    </div>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">
                            Styles
                            <span class="caret"></span>
                        </a>
                        <ul class="dropdown-menu">
                            <li class="">
                                <a href="#" rel="panel-default">Default</a>
                            </li>
                            <li class="">
                                <a href="#" rel="panel-primary">Primary</a>
                            </li>
                            <li class="">
                                <a href="#" rel="panel-success">Success</a>
                            </li>
                            <li class="">
                                <a href="#" rel="panel-info">Info</a>
                            </li>
                            <li class="">
                                <a href="#" rel="panel-warning">Warning</a>
                            </li>
                            <li class="">
                                <a href="#" rel="panel-danger">Danger</a>
                            </li>
                        </ul>
                    </span>

                </span>
                <div class="preview">Panels</div>
                <div class="view">
                    <div class="panel panel-default">
                        <div class="panel-heading">
                            <h3 class="panel-title" contenteditable="true">Panel title</h3>
                        </div>
                        <div class="panel-body" contenteditable="true">
                            Panel content
                        </div>
                        <div class="panel-footer" contenteditable="true">
                            Panel footer
                        </div>
                    </div>
                </div>
            </div>

        </li>
    </ul>

    <?php /* JavaScript Items which will not be in use.

    <ul class="nav nav-list accordion-group">
        <li class="nav-header">
            <i class="glyphicon glyphicon-plus"></i> JavaScript
            <div class="pull-right popover-info">
                <i class="glyphicon glyphicon-question-sign "></i>
                <div class="popover fade right">
                    <div class="arrow"></div>
                    <h3 class="popover-title">Help</h3>
                    <div class="popover-content">Drag &amp; Drop the elements inside the columns where you want to insert it. And from there, you can configure the style of that javascript. If you need more info please visit  <a target="_blank" href="http://getbootstrap.com/javascript">JavaScript.</a></div>
                </div>
            </div>
        </li>
        <li class="boxes mute" id="elmJS">
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger"><i class="glyphicon glyphicon-remove"></i> remove</a>
                <span class="drag label label-default ui-draggable-handle"><i class="glyphicon glyphicon-move"></i> drag</span>
                <?php print $edit; ?>
                <div class="preview">Modal</div>
                <div class="view">
                    <!-- Button to trigger modal -->
                    <a id="myModalLink" href="#myModalContainer" role="button" class="btn" data-toggle="modal">Launch demo modal</a>

                    <!-- Modal -->
                    <div class="modal fade" id="myModalContainer" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                        <div class="modal-dialog">
                            <div class="modal-content">
                                <div class="modal-header">
                                    <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
                                    <h4 class="modal-title" id="myModalLabel" contenteditable="true">Modal title</h4>
                                </div>
                                <div class="modal-body" contenteditable="true">
                                    ...
                                </div>
                                <div class="modal-footer">
                                    <button type="button" class="btn btn-default" data-dismiss="modal" contenteditable="true">Close</button>
                                    <button type="button" class="btn btn-primary" contenteditable="true">Save changes</button>
                                </div>
                            </div><!-- /.modal-content -->
                        </div><!-- /.modal-dialog -->
                    </div><!-- /.modal -->
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger"><i class="glyphicon glyphicon-remove"></i> remove</a>
                <span class="drag label label-default ui-draggable-handle"><i class="glyphicon glyphicon-move"></i> drag</span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">Position <span class="caret"></span></a>
                        <ul class="dropdown-menu">
                            <li class="active"><a href="#" rel="">Default</a></li>
                            <li class=""><a href="#" rel="navbar-static-top">Static top</a></li>
                            <li class=""><a href="#" rel="navbar-fixed-top">Navbar fixed top</a></li>
                            <li class=""><a href="#" rel="navbar-fixed-bottom">Navbar fixed bottom</a></li>
                        </ul>
                    </span>
                    <a class="btn btn-xs btn-default" href="#" rel="navbar-inverse">Inverse</a>
                    <!--a class="btn btn-xs btn-default" href="#" rel="navbar-static-top">Static top</a>
                    <a class="btn btn-mini" href="#" rel="navbar-fixed-top">Navbar fixed top</a>
                    <a class="btn btn-mini" href="#" rel="navbar-fixed-bottom">Navbar fixed bottom</a-->
                </span>
                <div class="preview">Navbar</div>
                <div class="view">
                    <nav class="navbar navbar-default" role="navigation">
                        <!-- Brand and toggle get grouped for better mobile display -->
                        <div class="navbar-header">
                            <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                                <span class="sr-only">Toggle navigation</span>
                                <span class="icon-bar"></span>
                                <span class="icon-bar"></span>
                                <span class="icon-bar"></span>
                            </button>
                            <a class="navbar-brand" href="#">Brand</a>
                        </div>
                        <!-- Collect the nav links, forms, and other content for toggling -->
                        <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                            <ul class="nav navbar-nav">
                                <li class="active"><a href="#">Link</a></li>
                                <li><a href="#">Link</a></li>
                                <li class="dropdown">
                                    <a href="#" class="dropdown-toggle" data-toggle="dropdown">Dropdown <b class="caret"></b></a>
                                    <ul class="dropdown-menu">
                                        <li><a href="#">Action</a></li>
                                        <li><a href="#">Another action</a></li>
                                        <li><a href="#">Something else here</a></li>
                                        <li class="divider"></li>
                                        <li><a href="#">Separated link</a></li>
                                        <li class="divider"></li>
                                        <li><a href="#">One more separated link</a></li>
                                    </ul>
                                </li>
                            </ul>
                            <form class="navbar-form navbar-left" role="search">
                                <div class="form-group">
                                    <input type="text" class="form-control" placeholder="Search">
                                </div>
                                <button type="submit" class="btn btn-default">Submit</button>
                            </form>
                            <ul class="nav navbar-nav navbar-right">
                                <li><a href="#">Link</a></li>
                                <li class="dropdown">
                                    <a href="#" class="dropdown-toggle" data-toggle="dropdown">Dropdown <b class="caret"></b></a>
                                    <ul class="dropdown-menu">
                                        <li><a href="#">Action</a></li>
                                        <li><a href="#">Another action</a></li>
                                        <li><a href="#">Something else here</a></li>
                                        <li class="divider"></li>
                                        <li><a href="#">Separated link</a></li>
                                    </ul>
                                </li>
                            </ul>
                        </div><!-- /.navbar-collapse -->
                    </nav>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger"><i class="glyphicon glyphicon-remove"></i> remove</a>
                <span class="drag label label-default ui-draggable-handle"><i class="glyphicon glyphicon-move"></i> drag</span>
                <?php print $edit; ?>
                <span class="configuration">
                </span>
                <div class="preview">Tabs</div>
                <div class="view">
                    <div class="tabbable" id="myTabs">
                        <!-- Only required for left/right tabs -->
                        <ul class="nav nav-tabs">
                            <li class="active"><a href="#tab1" data-toggle="tab" contenteditable="true">Section 1</a></li>
                            <li><a href="#tab2" data-toggle="tab" contenteditable="true">Section 2</a></li>
                        </ul>
                        <div class="tab-content">
                            <div class="tab-pane active" id="tab1">
                                <p contenteditable="true">I'm in Section 1.</p>
                            </div>
                            <div class="tab-pane" id="tab2">
                                <p contenteditable="true">Howdy, I'm in Section 2.</p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger"><i class="glyphicon glyphicon-remove"></i> remove</a>
                <span class="drag label label-default ui-draggable-handle"><i class="glyphicon glyphicon-move"></i> drag</span>
                <?php print $edit; ?>
                <span class="configuration">
                    <span class="btn-group btn-group-xs">
                        <a class="btn btn-default dropdown-toggle" data-toggle="dropdown" href="#">Styles <span class="caret"></span></a>
                        <ul class="dropdown-menu">
                            <li class=""><a href="#" rel="alert-success">Success</a></li>
                            <li class=""><a href="#" rel="alert-info">Info</a></li>
                            <li class=""><a href="#" rel="alert-warning">Warning</a></li>
                            <li class=""><a href="#" rel="alert-danger">Danger</a></li>
                        </ul>
                    </span>

                </span>
                <div class="preview">Alerts</div>
                <div class="view">
                    <div class="alert alert-success alert-dismissable" contenteditable="true">
                        <button type="button" class="close" data-dismiss="alert" aria-hidden="true">×</button>
                        <h4>Alert!</h4>
                        <strong>Warning!</strong> Best check yo self, you're not looking too good. <a href="#" class="alert-link">alert link</a>
                    </div>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger"><i class="glyphicon glyphicon-remove"></i> remove</a>
                <span class="drag label label-default ui-draggable-handle"><i class="glyphicon glyphicon-move"></i> drag</span>
                <?php print $edit; ?>
                <div class="preview">Collapse</div>
                <div class="view">
                    <div class="panel-group" id="myAccordion">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                <a class="panel-title" data-toggle="collapse" data-parent="#myAccordion" href="#collapseOne" contenteditable="true">
                                    Collapsible Group Item #1
                                </a>
                            </div>
                            <div id="collapseOne" class="panel-collapse collapse in">
                                <div class="panel-body" contenteditable="true">
                                    Anim pariatur cliche...
                                </div>
                            </div>
                        </div>
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                <a class="panel-title" data-toggle="collapse" data-parent="#myAccordion" href="#collapseTwo" contenteditable="true">
                                    Collapsible Group Item #2
                                </a>
                            </div>
                            <div id="collapseTwo" class="panel-collapse collapse">
                                <div class="panel-body" contenteditable="true">
                                    Anim pariatur cliche...
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger"><i class="glyphicon glyphicon-remove"></i> remove</a>
                <span class="drag label label-default ui-draggable-handle"><i class="glyphicon glyphicon-move"></i> drag</span>
                <?php print $edit; ?>
                <div class="preview">Carousel</div>
                <div class="view">


                    <div class="carousel slide" id="myCarousel">
                        <ol class="carousel-indicators">
                            <li class="active" data-slide-to="0" data-target="#myCarousel"></li>
                            <li data-slide-to="1" data-target="#myCarousel" class=""></li>
                            <li data-slide-to="2" data-target="#myCarousel" class=""></li>
                        </ol>
                        <div class="carousel-inner">
                            <div class="item active">
                                <img alt="Carousel Bootstrap First" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/sports-q-c-1600-500-1.jpg">
                                <div class="carousel-caption">
                                    <h4>First Thumbnail label</h4>
                                    <p>Cras justo odio, dapibus ac facilisis in, egestas eget quam. Donec id elit non mi porta gravida at eget metus. Nullam id dolor id nibh ultricies vehicula ut id elit.</p>
                                </div>
                            </div>
                            <div class="item">
                                <img alt="Carousel Bootstrap Second" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/sports-q-c-1600-500-2.jpg">
                                <div class="carousel-caption">
                                    <h4>Second Thumbnail label</h4>
                                    <p>Cras justo odio, dapibus ac facilisis in, egestas eget quam. Donec id elit non mi porta gravida at eget metus. Nullam id dolor id nibh ultricies vehicula ut id elit.</p>
                                </div>
                            </div>
                            <div class="item">
                                <img alt="Carousel Bootstrap Third" src="<?php print drupal_get_path('module', 'eddy_seo_drag_and_drop_editor') ?>/images/sports-q-c-1600-500-3.jpg">
                                <div class="carousel-caption">
                                    <h4>Third Thumbnail label</h4>
                                    <p>Cras justo odio, dapibus ac facilisis in, egestas eget quam. Donec id elit non mi porta gravida at eget metus. Nullam id dolor id nibh ultricies vehicula ut id elit.</p>
                                </div>
                            </div>
                        </div>
                        <a class="left carousel-control" href="#myCarousel" data-slide="prev">
                            <span class="glyphicon glyphicon-chevron-left"></span>
                        </a>
                        <a class="right carousel-control" href="#myCarousel" data-slide="next">
                            <span class="glyphicon glyphicon-chevron-right"></span>
                        </a>
                    </div>
                </div>
            </div>
        </li>
    </ul>
    End of JS Components */ ?>
    <?php if($valid_eddy_form): //only display eddy form components if there is eddy form been created?>
    <ul class="nav nav-list accordion-group">
        <li class="nav-header">
            <i class="glyphicon glyphicon-plus"></i>
            EDDY Form
            <div class="pull-right popover-info">
                <i class="glyphicon glyphicon-question-sign "></i>
                <div class="popover fade right">
                    <div class="arrow"></div>
                    <h3 class="popover-title">Help</h3>
                    <div class="popover-content">
                        Drag &amp; Drop the elements inside the columns where you want to insert it. And from there, you can configure the style of that javascript. If you need more info please visit
                        <a target="_blank" href="http://getbootstrap.com/javascript">JavaScript.</a>
                    </div>
                </div>
            </div>
        </li>
        <li class="boxes mute" id="elmEDDY">

            <div class="box box-element ui-draggable">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">Wizard Form</div>
                <div class="view">
                    <div class="eddy-form-container" name="eddy-form-container">EDDY Form Loading...</div>
                </div>
            </div>
            <div class="box box-element ui-draggable program-info-container description-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">Program Info</div>
                <div class="view">
                    <div class="div-program-info">
                        <h2 class="program-info" contenteditable="true">Heading</h2>
                        <div contenteditable="true">
                            <p class="program-name" contenteditable="true">[Program Name]</p>
                            <p class="program-description" contenteditable="true">[Program Description]</p>
                            <p class="program-disclaimer" contenteditable="true">[Program Disclaimer]</p>
                        </div>
                    </div>
                </div>
            </div>
            <div class="box box-element ui-draggable workflow-container-holder start-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">Form Start</div>
                <div class="view">
                    <div class="workflow-container start-container">
                        <h2 contenteditable="true">Heading</h2>
                        <p contenteditable="true">Cras sit amet nibh libero, in gravida nulla. Nulla vel metus scelerisque ante sollicitudin commodo. Cras purus odio, vestibulum in vulputate at, tempus viverra turpis.</p>
                    </div>
                </div>
            </div>

            <div class="box box-element ui-draggable workflow-container-holder managedchoice-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">Managed Choice</div>
                <div class="view">
                    <div class="workflow-container managedchoice-container">
                        <h2 contenteditable="true">Heading</h2>
                        <p contenteditable="true">Cras sit amet nibh libero, in gravida nulla. Nulla vel metus scelerisque ante sollicitudin commodo. Cras purus odio, vestibulum in vulputate at, tempus viverra turpis.</p>
                    </div>
                </div>
            </div>

            <div class="box box-element ui-draggable workflow-container-holder nomatch-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">No Match</div>
                <div class="view">
                    <div class="workflow-container nomatch-container">
                        <h2 contenteditable="true">Heading</h2>
                        <p contenteditable="true">Cras sit amet nibh libero, in gravida nulla. Nulla vel metus scelerisque ante sollicitudin commodo. Cras purus odio, vestibulum in vulputate at, tempus viverra turpis.</p>
                    </div>
                </div>
            </div>

            <div class="box box-element ui-draggable workflow-container-holder thankyou-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">Thank You</div>
                <div class="view">
                    <div class="workflow-container thankyou-container">
                        <h2 contenteditable="true">Heading</h2>
                        <p contenteditable="true">Cras sit amet nibh libero, in gravida nulla. Nulla vel metus scelerisque ante sollicitudin commodo. Cras purus odio, vestibulum in vulputate at, tempus viverra turpis.</p>
                    </div>
                </div>
            </div>

            <div class="box box-element ui-draggable workflow-container-holder nothankyou-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">No Thank You</div>
                <div class="view">
                    <div class="workflow-container nothankyou-container">
                        <h2 contenteditable="true">Heading</h2>
                        <p contenteditable="true">Cras sit amet nibh libero, in gravida nulla. Nulla vel metus scelerisque ante sollicitudin commodo. Cras purus odio, vestibulum in vulputate at, tempus viverra turpis.</p>
                    </div>
                </div>
            </div>

            <div class="box box-element ui-draggable step-container">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle display-none">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">
                    <input type="text" value="" placeholder="Enter a Step Number" class="form-control" />
                </div>
                <div class="view">
                    <div class="step-view-holder">
                        <h2 contenteditable="true">
                            Step
                            <span></span>
                            Text
                        </h2>
                        <p contenteditable="true">
                            This content will only exist on Step
                            <span></span>
                            of the funnel.
                        </p>
                    </div>
                </div>
            </div>

        </li>

    </ul>

    <ul class="nav nav-list accordion-group">

        <li class="nav-header">
            <i class="glyphicon glyphicon-plus"></i>
            Form Defaults
            <div class="pull-right popover-info">
                <i class="glyphicon glyphicon-question-sign "></i>
                <div class="popover fade right">
                    <div class="arrow"></div>
                    <h3 class="popover-title">Help</h3>
                    <div class="popover-content">
                        Drag &amp; Drop the elements inside the columns where you want to insert it. And from there, you can configure the style of that javascript. If you need more info please visit
                        <a target="_blank" href="http://getbootstrap.com/javascript">JavaScript.</a>
                    </div>
                </div>
            </div>
        </li>
        <li class="boxes mute" id="elmEDDYPD">

            <div class="box box-element ui-draggable workflow-container-holder managedchoice-container-holder pd-managedchoice-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">Managed Choice</div>
                <div class="view">
                    <div class="workflow-container managedchoice-container">
                        [property:default_manage_choice]
                    </div>
                </div>
            </div>

            <div class="box box-element ui-draggable workflow-container-holder nomatch-container-holder pd-nomatch-ads-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <?php print $edit; ?>
                <div class="preview">No Match Ads</div>
                <div class="view">
                    <div class="eddy-form-wizard-container workflow-container nomatch-container" id="nomatch-ads-container">
                        <div class="eddy-form-wizard-header" id="eddy-form-wizard-nomatch-header">&nbsp;</div>
                        <div class="eddy-form-wizard-body">
                            <div class="form-page-step-message-nomatch">
                                <h3>
                                    <strong>Sorry but you did not match any of our Schools</strong>
                                </h3>
                                <p>See below for some schools you may be interested in</p>
                            </div>
                            <div id="nomatch_ads_listing">[property:default_nomatch_ads]</div>
                        </div>
                        <div class="eddy-form-wizard-footer-nomatch clearfix"></div>
                    </div>
                </div>
            </div>

            <div class="box box-element ui-draggable workflow-container-holder nomatch-container-holder pd-nomatch-content-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">No Match Content</div>
                <div class="view">
                    <div class="workflow-container nomatch-container">
                        [property:default_nomatch_content]
                    </div>
                </div>
            </div>

            <div class="box box-element ui-draggable workflow-container-holder thankyou-container-holder pd-thankyou-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">Thank You</div>
                <div class="view">
                    <div class="workflow-container thankyou-container">
                        [property:default_thankyou]
                    </div>
                </div>
            </div>

            <div class="box box-element ui-draggable workflow-container-holder nothankyou-container-holder pd-nothankyou-container-holder">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">No Thank You</div>
                <div class="view">
                    <div class="workflow-container nothankyou-container">
                        [property:default_nothankyou]
                    </div>
                </div>
            </div>

        </li>

    </ul>
    <?php endif; ?>

    <ul class="nav nav-list accordion-group">

        <li class="nav-header">
            <i class="glyphicon glyphicon-plus"></i>
            Page Items
            <div class="pull-right popover-info">
                <i class="glyphicon glyphicon-question-sign "></i>
                <div class="popover fade right">
                    <div class="arrow"></div>
                    <h3 class="popover-title">Help</h3>
                    <div class="popover-content">
                        Drag &amp; Drop the elements inside the columns where you want to insert it. And from there, you can configure the style of that javascript. If you need more info please visit
                        <a target="_blank" href="http://getbootstrap.com/javascript">JavaScript.</a>
                    </div>
                </div>
            </div>
        </li>
        <li class="boxes mute" id="elmEDDYPage">

            <div class="box box-element ui-draggable page-logo">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">Page Logo</div>
                <div class="view">
                    <div class="page-logo-holder">[page:logo]</div>
                </div>
            </div>

            <div class="box box-element ui-draggable page-logo">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">Trust-e</div>
                <div class="view">
                    <div class="page-logo-holder">[page:truste]</div>
                </div>
            </div>

            <div class="box box-element ui-draggable page-copyright">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">Copyright</div>
                <div class="view">
                    <div class="page-copyright">[page:copyright]</div>
                </div>
            </div>

            <div class="box box-element ui-draggable page-footer-links">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">Footer Links</div>
                <div class="view">
                    <div class="page-footer-links">[page:footer_links]</div>
                </div>
            </div>

        </li>

    </ul>

    <ul class="nav nav-list accordion-group latest-group-sidebar">

        <li class="nav-header">
            <i class="glyphicon glyphicon-plus"></i>
            Property Items
            <div class="pull-right popover-info">
                <i class="glyphicon glyphicon-question-sign "></i>
                <div class="popover fade right">
                    <div class="arrow"></div>
                    <h3 class="popover-title">Help</h3>
                    <div class="popover-content">
                        Drag &amp; Drop the elements inside the columns where you want to insert it. And from there, you can configure the style of that javascript. If you need more info please visit
                        <a target="_blank" href="http://getbootstrap.com/javascript">JavaScript.</a>
                    </div>
                </div>
            </div>
        </li>
        <li class="boxes mute" id="elmEDDYProperty">

            <div class="box box-element ui-draggable property-name">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">Property Name</div>
                <div class="view">
                    <div class="page-logo-holder">[property:name]</div>
                </div>
            </div>

            <div class="box box-element ui-draggable property-host-name">
                <a href="#close" class="remove label label-danger">
                    <i class="glyphicon glyphicon-remove"></i>
                    remove
                </a>
                <span class="drag label label-default ui-draggable-handle">
                    <i class="glyphicon glyphicon-move"></i>
                    drag
                </span>
                <div class="preview">Host Name</div>
                <div class="view">
                    <div class="page-logo-holder">[property:host_name]</div>
                </div>
            </div>

        </li>

    </ul>


</div>
