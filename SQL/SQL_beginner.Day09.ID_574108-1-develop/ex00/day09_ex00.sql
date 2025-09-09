create table person_audit (
    created    timestamp with time zone NOT NULL DEFAULT current_timestamp,
    type_event char(1)                  NOT NULL DEFAULT 'I',
    row_id     bigint                   NOT NULL,
    name       varchar,
    age        integer,
    gender     varchar,
    address    varchar,
    constraint ch_type_event check (type_event in ('I', 'D', 'U'))
);

create or replace function fnc_trg_person_insert_audit()
    returns trigger
    language PLPGSQL as
$BODY$
begin
    insert into person_audit(created, type_event, row_id, name, age, gender, address)
    values (current_timestamp, 'I', NEW.id, NEW.name, NEW.age, NEW.gender, NEW.address);
    return null;
end;
$BODY$;

create trigger trg_person_insert_audit
after insert
	on person
for each row
execute function fnc_trg_person_insert_audit();

insert into person(id, name, age, gender, address)
values (10, 'Damir', 22, 'male', 'Irkutsk');

select *
from person_audit;