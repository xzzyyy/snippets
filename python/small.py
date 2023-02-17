import datetime
import time


class ScopedInstanceClass:
    def __enter__(self):
        print("enter called!")

    def __exit__(self, ext_type, ext_value, traceback):
        print("exit called!")


def utc2local(utc):
    epoch = time.mktime(utc.timetuple())
    offset = datetime.datetime.fromtimestamp(epoch) - datetime.datetime.utcfromtimestamp(epoch)
    return utc + offset


def print_header(caption: str):
    print()
    print()
    print(caption)
    print('---------------------------------------')


print_header('scoped instance')
with ScopedInstanceClass() as inst:
    print("inside with")
print("outside with")


print_header('UTC to local')
utc_time = datetime.datetime.utcnow()
print('UTC time:   %s' % utc_time)
print('local time: %s' % utc2local(utc_time))
