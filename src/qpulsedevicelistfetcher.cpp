#include <stdio.h>
#include <string.h>

#include <pulse/pulseaudio.h>

#include "qpulsedevicelistfetcher.h"

// https://www.freedesktop.org/wiki/Software/PulseAudio/Documentation/Developer/Clients/Samples/AsyncDeviceList/

typedef struct
{
    QList<QPulseDeviceEntry *> result;
    bool wantSources;
    int pa_ready;
    int action;
} FetchState;

void pa_state_cb(pa_context *c, void *userdata)
{
    FetchState *cs = (FetchState *)userdata;
    pa_context_state_t state = pa_context_get_state(c);

    switch (state) {
        case PA_CONTEXT_UNCONNECTED:
        case PA_CONTEXT_CONNECTING:
        case PA_CONTEXT_AUTHORIZING:
        case PA_CONTEXT_SETTING_NAME:
        default:
            break;
        case PA_CONTEXT_FAILED:
        case PA_CONTEXT_TERMINATED:
            cs->pa_ready = 2;
            break;
        case PA_CONTEXT_READY:
            cs->pa_ready = 1;
            break;
    }
}

#define SINK_SOURCE_CB(which, type) \
void get_##which(pa_context *c, const type *info, int eol, void *userdata) \
{ \
    if (eol) \
        return; \
 \
    FetchState *cs = (FetchState *)userdata; \
    QPulseDeviceEntry *e = new QPulseDeviceEntry(info->name, info->description, \
            info->index); \
 \
    cs->result.append(e); \
}

SINK_SOURCE_CB(sink, pa_sink_info)
SINK_SOURCE_CB(source, pa_source_info)

void get_devicelist(FetchState *cs)
{
    pa_context *pa_ctx;
    pa_mainloop_api *pa_mlapi;
    pa_mainloop *pa_ml;
    pa_operation *pa_op;

    pa_ml = pa_mainloop_new();
    pa_mlapi = pa_mainloop_get_api(pa_ml);
    pa_ctx = pa_context_new(pa_mlapi, "test");

    cs->pa_ready = 0;
    cs->action = 0;
    cs->result = QList<QPulseDeviceEntry *>();

    pa_context_connect(pa_ctx, NULL, (pa_context_flags_t)0, NULL);
    pa_context_set_state_callback(pa_ctx, pa_state_cb, cs);

    for (;;) {
        if (cs->pa_ready == 0) {
            pa_mainloop_iterate(pa_ml, 1, NULL);
            continue;
        }
        else if (cs->pa_ready == 2) {
            pa_context_disconnect(pa_ctx);
            pa_context_unref(pa_ctx);
            pa_mainloop_free(pa_ml);
            return;
        }
        switch (cs->action) {
            case 0:
                if (cs->wantSources)
                    pa_op = pa_context_get_source_info_list(pa_ctx, get_source,
                            cs);
                else
                    pa_op = pa_context_get_sink_info_list(pa_ctx, get_sink, cs);

                cs->action++;
                break;
            case 1:
                if (pa_operation_get_state(pa_op) == PA_OPERATION_DONE) {
                    pa_operation_unref(pa_op);
                    pa_context_disconnect(pa_ctx);
                    pa_context_unref(pa_ctx);
                    pa_mainloop_free(pa_ml);
                    return;
                }
                break;
            default:
                return;
        }

        pa_mainloop_iterate(pa_ml, 1, NULL);
    }
}

QList<QPulseDeviceEntry *> QPulseDeviceListFetcher::readSourceInputs(void)
{
    FetchState cs;

    cs.wantSources = 1;
    get_devicelist(&cs);
    return cs.result;
}

QList<QPulseDeviceEntry *> QPulseDeviceListFetcher::readSinkOutputs(void)
{
    FetchState cs;

    cs.wantSources = 0;
    get_devicelist(&cs);
    return cs.result;
}
