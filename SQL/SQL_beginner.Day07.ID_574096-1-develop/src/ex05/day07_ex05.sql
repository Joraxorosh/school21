select distinct name
from person as p
join person_order as po on p.id = po.person_id
order by 1;