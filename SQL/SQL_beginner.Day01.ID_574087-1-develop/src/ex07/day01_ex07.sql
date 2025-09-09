select person_order.order_date as order_date, (person.name || '(age:' || person.age || ')') as person_information
from person_order
join person on person_order.person_id = person.id
order by order_date asc, person_information asc