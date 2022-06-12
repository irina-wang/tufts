signature SORT = sig
    type elem
    val compare : elem * elem -> order
    val sort : elem list -> elem list (* return increasing *)
end

functor MPQSortFn(structure Q : MPQUEUE) :> SORT 
    where type elem = Q.elem = 
struct
    type elem = Q.elem
    val compare = Q.compare_elem
    fun sort data = 
        let val heap = Q.new()
            val insert = List.map (fn n => Q.insert(n,heap)) data
            fun extract minheap =  
                if Q.isEmpty heap then []
                else let val min = Q.deletemin minheap
                      in min :: extract minheap
                      end
        in extract heap
        end
end