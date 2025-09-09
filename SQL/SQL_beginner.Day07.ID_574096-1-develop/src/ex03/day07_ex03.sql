select coalesce(po.name, pv.name) as name, coalesce(po.count, 0) + coalesce(pv.count, 0) as total_count
from (select p.name, count(*) as count
      from person_order po
      join menu as m 
	  	on m.id = po.menu_id
      join pizzeria as p 
	  	on p.id = m.pizzeria_id
      group by p.name) as po
full outer join (select p.name, count(*) as count
                 from person_visits as pv
                 join pizzeria as p on p.id = pv.pizzeria_id
                 group by p.name) as pv 
	on po.name = pv.name
order by total_count desc, name;