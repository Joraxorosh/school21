create index idx_person_name on person(upper(name));
set ENABLE_SEQSCAN = off;
explain analyze
select name
from person
where upper(name) = 'KATE';