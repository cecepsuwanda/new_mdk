<?php require_once('shared.php');
     
class dt_fam_ind_detail
{
   private $tb_;
   
   function __construct() {
	$this->tb_ = new tb_gen('dbo_fam_ind_detail');
   }

   function getdata($where)
   {
     $data = $this->tb_->getData($where);
     return empty($data) ? array() : $data;
   }

   function insert_data($data)
   {
     $this->tb_->insertRecord($data);
   }

   public function updatedata($field,$where)
   {
      $this->tb_->updateAllRecord($field,$where);       
   }

   function get_ind_ks($kki)
   {
     $this->tb_->sql_orderby='id_ind_ks,kd_prospinstat';
     $data = $this->getdata("Kd_fam='$kki'");

     $ind_ks=array();
     if(!empty($data))
     {
       foreach ($data as $row) {
         	$ind_ks[$row['id_ind_ks']]=$row['kd_prospinstat'];
         }  
     } 

     return $ind_ks;
   }

   function delete_data($data)
   {
     $this->tb_->deleteRecord($data); 
   }

}