<?php

/**
 * @todo:
 * finish this file according to the .install
 */

function hook_views_data() {

  // First, the entry $data['payments']['table'] describes properties of
  // the actual table – not its content.

  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.
  $data['payments']['table']['group'] = t('Payments');

  // Define this as a base table – a table that can be described in itself by
  // views (and not just being brought in as a relationship). 
  $data['payments']['table']['base'] = array(
    'field' => 'pid', // This is the identifier field for the view.
    'title' => t('payments'),
    'weight' => -10,
  );

  // Next, describe each of the individual fields in this table to Views. This
  // is done by describing $data['payments']['FIELD_NAME']. This part of
  // the array may then have further entries:
  //   - title: The label for the table field, as presented in Views.
  //   - help: The description text for the table field.
  //   - relationship: A description of any relationship handler for the table
  //     field.
  //   - field: A description of any field handler for the table field.
  //   - sort: A description of any sort handler for the table field.
  //   - filter: A description of any filter handler for the table field.
  //   - argument: A description of any argument handler for the table field.
  //   - area: A description of any handler for adding content to header,
  //     footer or as no result behaviour.
  //
  // The handler descriptions are described with examples below.

  $data['payments']['pid'] = array(
    'title' => t('Payment ID'),

    // Define a relationship to the order_items table, so payments views can
    // add a relationship to order items. If you want to define a relationship the
    // other direction, use hook_views_data_alter(), or use the 'implicit' join
    // method described above.
    'relationship' => array(
      'base' => 'order_items', // The name of the table to join with.
      'base field' => 'pid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship',
      'label' => t('Order Items'),
      'title' => t('Order Items'),
    ),
  );

  $data['payments']['paid'] = array(
    'title' => t('Paid'),
    'help' => t('Has the payment been paid, or just generated?'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      
      // Note that you can override the field-wide label:
      'label' => t('Paid'),
      
      // This setting is used by the boolean filter handler, as possible option.
      'type' => 'yes-no',
      
      // use boolean_field = 1 instead of boolean_field <> 0 in WHERE statment.
      'use equal' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

    // Example timestamp field.
    $data['payments']['date_modified'] = array(
      'title' => t('Payment Date'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    );








  // First, the entry $data['order_items']['table'] describes properties of
  // the actual table – not its content.

  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.
  $data['order_items']['table']['group'] = t('Order Items');

  // Define this as a base table – a table that can be described in itself by
  // views (and not just being brought in as a relationship).
  $data['order_items']['table']['base'] = array(
    'field' => 'oiid', // This is the identifier field for the view.
    'title' => t('Order Items'),
    'weight' => -10,
  );

  // This table references the {node} table. The declaration below creates an
  // 'implicit' relationship to the node table, so that when 'node' is the base
  // table, the fields are automatically available.
  $data['order_items']['table']['join'] = array(

    // Index this array by the table name to which this table refers.
    // 'left_field' is the primary key in the referenced table.
    // 'field' is the foreign key in this table.
    'node' => array(
      'left_field' => 'nid',
      'field' => 'entity_id',
    ),

    'payments' => array(
        'left_field' => 'oid',
        'field' => 'oid',
    )
  );

  // Next, describe each of the individual fields in this table to Views. This
  // is done by describing $data['order_items']['FIELD_NAME']. This part of
  // the array may then have further entries:
  //   - title: The label for the table field, as presented in Views.
  //   - help: The description text for the table field.
  //   - relationship: A description of any relationship handler for the table
  //     field.
  //   - field: A description of any field handler for the table field.
  //   - sort: A description of any sort handler for the table field.
  //   - filter: A description of any filter handler for the table field.
  //   - argument: A description of any argument handler for the table field.
  //   - area: A description of any handler for adding content to header,
  //     footer or as no result behaviour.
  //
  // The handler descriptions are described with examples below.

  // Node ID table field.
  $data['order_items']['oiid'] = array(
    'title' => t('Order Item ID'),
  );

  // Example numeric text field.
  $data['order_items']['entity_id'] = array(
    'title' => t('Ordered Item Node'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Define a relationship to the {node} table, so order_items views can
    // add a relationship to nodes. If you want to define a relationship the
    // other direction, use hook_views_data_alter(), or use the 'implicit' join
    // method described above.
    'relationship' => array(
      'base' => 'node', // The name of the table to join with.
      'base field' => 'nid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship',
      'label' => t('Ordered Item Node'),
      'title' => t('Ordered Item Node'),
    ),
  );

  // Example numeric text field.
    $data['order_items']['amount'] = array(
      'title' => t('Amount Ordered'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );

  // Example numeric text field.
    $data['order_items']['oid'] = array(
      'title' => t('Order ID'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      // Define a relationship to the payments table, so order_items views can
      // add a relationship to payments. If you want to define a relationship the
      // other direction, use hook_views_data_alter(), or use the 'implicit' join
      // method described above.
      'relationship' => array(
        'base' => 'payments', // The name of the table to join with.
        'base field' => 'oid', // The name of the field on the joined table.
        'handler' => 'views_handler_relationship',
        'label' => t('Order ID'),
        'title' => t('Order ID'),
      ),
    );



  return $data;
}