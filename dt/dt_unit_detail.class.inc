<?php require_once('shared.php');
     
class dt_unit_detail
{

   private $tb_;
   
   function __construct() {
	  $this->tb_ = new tb_gen('dbo_unit_detail');
	  $this->tb_->sql_orderby = 'no_unit_detail';
   }

   public function getdata($where)
   {
      $data =  $this->tb_->getdata($where); 
      return $data;
   }

   public function getjml($idunit,$kd)
   {
      $tmp=$this->getdata("id_unit_detail LIKE '$idunit%' AND id_unit_detail_idk LIKE '$idunit%' AND id_unit=$kd");
      return $this->getnumrows();
   }

   public function getnumrows()
   {
      return $this->tb_->numrows;
   }

   public function getKec()
   {
      $data = $this->tb_->getdata('id_unit=11 AND id_unit_detail_idk=1017');
      return $data;	
   } 

   public function getdesa($kdkec)
   {
      $data = $kdkec=='' ? array() : $this->tb_->getdata("id_unit=12 AND id_unit_detail_idk=$kdkec");
      return $data;  
   }

   public function getdusun($kddesa)
   {
      $data = $kddesa=='' ? array() : $this->tb_->getdata("id_unit=13 AND id_unit_detail_idk=$kddesa");
      return $data;  
   }

   public function getRT($kddusun)
   {
      $data = $kddusun=='' ? array() : $this->tb_->getdata("id_unit=14 AND id_unit_detail_idk=$kddusun");
      return $data;  
   } 

   public function getnm($where)
   {
	  $data=$this->tb_->getData($where);
      return (isset($data[0]['no_unit_detail']) ? $data[0]['no_unit_detail'] : '');
   }

}
?>