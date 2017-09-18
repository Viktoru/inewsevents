<?php
/**
 * Implements hook_perm().
 */
function inewsevents_get_records() {
  $output = '';
  $rows = array();
  $header = array(
    'User',
    'Title',
    'Description',
    'Date',
  );
  $fields = drupal_get_schema('inewsevents');
  $query = db_select('inewsevents', 'm');
  $results = $query->fields('m', array_keys($fields['fields']))
    ->execute()
    ->fetchAll();

  foreach ($results as $value) {
    $account = $value->uid ? user_load($value->uid) : '';
    $rows[] = array(
      $value->uid ? theme('username', array('account' => $account)) : '',
//      $value->nid ? l($value->shortdescription, 'node/'.$value->nid) : '',
      $value->shortdescription,
      $value->longdescription,
      $value->columndate,
    );
  }
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  return $output;
}