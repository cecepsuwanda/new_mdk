<?php require_once('shared.php');
     
class dt_typeuser
{

   function __construct() {

   }

   function gettypeuserlst($idunit)
   {
      $tb = new tb_gen('tbgen');
      $tb->sql_select = '*'; 
	  $tb->sql_from = 'dbo_typeuser_unit_detail dtu inner join dbo_typeuser dt on dtu.id_typeuser=dt.id_typeuser';
	  $tb->sql_where = "dtu.id_unit_detail='$idunit' AND dt.id_typeuser_idk IS NULL";

	  $data = $tb->getData('');
	  return $data;
   }

   function isunithavetypeuser($idunit)
   {
   	
   }

}

?>	