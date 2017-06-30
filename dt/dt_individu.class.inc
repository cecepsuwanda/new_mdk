<?php require_once('shared.php');
     
class dt_individu
{
   private $tb_;
   
   function __construct() {
	$this->tb_ = new tb_gen('dbo_individu');
   }

   public function getdata($where)
   {
     $this->tb_->sql_orderby = 'Kd_indv,Kd_fammbrtyp';
     $data = $this->tb_->getData($where);
     return empty($data) ? array() : $data;
   }

   public function getkak($iddesa)
   {
     $this->tb_->sql_select = 'Kd_unik_indv';
     $this->tb_->sql_orderby = 'Kd_unik_indv desc'; 
     $data = $this->tb_->getData("kd_indv like '$iddesa%'");  

     $tmp_kak = '0000001';
     if(!empty($data))
     {
       $tmp_kak = str_pad(intval($data[0]['Kd_unik_indv'])+1,7,'0',STR_PAD_LEFT);
     }
     return $tmp_kak;

   }

   function insert_data($data)
   {
     $this->tb_->insertRecord($data);
   }

   public function updatedata($field,$where)
   {
      $this->tb_->updateAllRecord($field,$where);       
   }


   function kak_exist($kak)
   {
     $data = $this->tb_->getData("Kd_indv='$kak'");
     return empty($data) ? 0 : 1;
   }

   function delete_data($data)
   {     
     $this->tb_->deleteAllRecord($data); 
   }

}   