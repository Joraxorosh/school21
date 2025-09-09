select order_date as action_date, person_id
from person_order
intersect all
select visit_date as action_date, person_id
from person_visits
order by action_date asc, person_id desc