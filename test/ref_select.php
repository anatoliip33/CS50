<?php

    $array = [3, 5, 2, 6, 4];
    
    function selection($array)
    {
        foreach ($array as $i => $value_i)
        {
            $smallest = $value_i;
            $position = $i;
            foreach($array as $j => $value_j)
            {
                if($value_j<$smallest)
                {
                    $smallest = $value_j;
                    $position = $j;
                }
            }
            $temp = $value_i;
            $value_i = $smallest;
            $value_j = $temp;
        }
        return $array;
    };
    
    $sort_array = selection($array);
    
    print_r($sort_array);
?>