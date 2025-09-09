drop trigger if exists trg_person_insert_audit on person;
drop trigger if exists trg_person_update_audit on person;
drop trigger if exists trg_person_delete_audit on person;

drop function if exists fnc_trg_person_insert_audit;
drop function if exists fnc_trg_person_update_audit;
drop function if exists fnc_trg_person_delete_audit;

-- drop trigger if exists trg_person_audit on person;
-- drop function if exists fnc_trg_person_audit;

truncate table person_audit;

create or replace function fnc_trg_person_audit()
returns trigger as $$
begin
    if TG_OP = 'INSERT' then
        insert into person_audit (created, type_event, row_id, name, age, gender, address)
        values (current_timestamp, 'I', NEW.id, NEW.name, NEW.age, NEW.gender, NEW.address);
    elsif TG_OP = 'UPDATE' then
        insert into person_audit (created, type_event, row_id, name, age, gender, address)
        values (current_timestamp, 'U', OLD.id, OLD.name, OLD.age, OLD.gender, OLD.address);
    elsif TG_OP = 'DELETE' then
        insert into person_audit (created, type_event, row_id, name, age, gender, address)
        values (current_timestamp, 'D', OLD.id, OLD.name, OLD.age, OLD.gender, OLD.address);
    end if;
    return null;
end;
$$ language plpgsql;

create trigger trg_person_audit
after insert or update or delete on person
for each row
execute function fnc_trg_person_audit();

insert into person (id, name, age, gender, address) values (10, 'Damir', 22, 'male', 'Irkutsk');
update person set name = 'Bulat' where id = 10;
update person set name = 'Damir' where id = 10;
delete from person where id = 10;

select * from person_audit where row_id = 10;