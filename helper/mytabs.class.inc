<?php

  require_once 'shared.php';

class mytabs
{
    var $id_;
    var $header_;
    var $content_;	
	 
	 function __construct($id,$header,$content)
	 {
	  	$this->id_=$id;
        $this->header_=$header;
        $this->content_=$content;	  
	 }

     function display($onclick='')
     {
        $html_txt = '<div id="'.$this->id_.'">';
        
		$html_txt.="<ul>";
        if(!empty($this->header_))
		{  $i=1;
		   foreach($this->header_ as $header)
		   {
		     $html_txt.="<li><a href='#".$this->id_."-".$i."' ".$onclick.">".$header."</a></li>";
			 $i++;
		   }
		
		}
        $html_txt.="</ul>";
		if(!empty($this->content_))
		{ $i=1;
		  foreach($this->content_ as $content)
		   {
		     $html_txt.="<div id='".$this->id_."-".$i."'>".$content."</div>";
			 $i++;
		   }
		
		}
		
        $html_txt .='</div>';

        return $html_txt;		
     }	 
}


?>