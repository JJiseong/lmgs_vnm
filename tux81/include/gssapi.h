/* #ident	"@(#) gp/sec/include/gssapi.h	$Revision: 1.2 $" */

/* Taken from RFC 1509 */

#ifndef GSSAPI_H_
#define GSSAPI_H_

/*
 * First, define the platform-dependent types.
 */
typedef TM32U OM_uint32;
typedef void *gss_ctx_id_t;
typedef void *gss_cred_id_t;
/* typedef <platform-specific> gss_name_t; - defined below */

/*
 * Note that a platform supporting the xom.h X/Open header file
 * may make use of that header for the definitions of OM_uint32
 * and the structure to which gss_OID_desc equates.
 */

typedef struct gss_OID_desc_struct {
      OM_uint32 length;
      void      *elements;
} gss_OID_desc, *gss_OID;

typedef struct gss_OID_set_desc_struct  {
      int     count;
      gss_OID elements;
} gss_OID_set_desc, *gss_OID_set;

typedef struct gss_name_struct
{
    gss_OID       type;
    OM_uint32     length;
    void          *elements;
} gss_name_desc, *gss_name_t;

typedef struct gss_buffer_desc_struct {
      OM_uint32 length;
      void *value;
} gss_buffer_desc, *gss_buffer_t;

typedef struct gss_channel_bindings_struct {
      OM_uint32 initiator_addrtype;
      gss_buffer_desc initiator_address;
      OM_uint32 acceptor_addrtype;
      gss_buffer_desc acceptor_address;
      gss_buffer_desc application_data;
} *gss_channel_bindings_t;


/*
 * Six independent flags each of which indicates that a context
 * supports a specific service option.
 */
#define GSS_C_DELEG_FLAG 1
#define GSS_C_MUTUAL_FLAG 2
#define GSS_C_REPLAY_FLAG 4
#define GSS_C_SEQUENCE_FLAG 8
#define GSS_C_CONF_FLAG 16
#define GSS_C_INTEG_FLAG 32


/*
 * Credential usage options
 */
#define GSS_C_BOTH 0
#define GSS_C_INITIATE 1
#define GSS_C_ACCEPT 2


/*
 * Status code types for gss_display_status
 */
#define GSS_C_GSS_CODE 1
#define GSS_C_MECH_CODE 2

/*
 * The constant definitions for channel-bindings address families
 */
#define GSS_C_AF_UNSPEC     0;
#define GSS_C_AF_LOCAL      1;
#define GSS_C_AF_INET       2;
#define GSS_C_AF_IMPLINK    3;
#define GSS_C_AF_PUP        4;
#define GSS_C_AF_CHAOS      5;
#define GSS_C_AF_NS         6;
#define GSS_C_AF_NBS        7;
#define GSS_C_AF_ECMA       8;
#define GSS_C_AF_DATAKIT    9;
#define GSS_C_AF_CCITT      10;
#define GSS_C_AF_SNA        11;
#define GSS_C_AF_DECnet     12;
#define GSS_C_AF_DLI        13;
#define GSS_C_AF_LAT        14;
#define GSS_C_AF_HYLINK     15;
#define GSS_C_AF_APPLETALK  16;
#define GSS_C_AF_BSC        17;
#define GSS_C_AF_DSS        18;
#define GSS_C_AF_OSI        19;
#define GSS_C_AF_X25        21;

#define GSS_C_AF_NULLADDR   255;

#define GSS_C_NO_BUFFER ((gss_buffer_t) 0)
#define GSS_C_NULL_OID ((gss_OID) 0)
#define GSS_C_NULL_OID_SET ((gss_OID_set) 0)
#define GSS_C_NO_CONTEXT ((gss_ctx_id_t) 0)
#define GSS_C_NO_CREDENTIAL ((gss_cred_id_t) 0)
#define GSS_C_NO_CHANNEL_BINDINGS ((gss_channel_bindings_t) 0)
#define GSS_C_EMPTY_BUFFER {0, NULL}

/*
 * Define the default Quality of Protection for per-message
 * services.  Note that an implementation that offers multiple
 * levels of QOP may either reserve a value (for example zero,
 * as assumed here) to mean "default protection", or alternatively
 * may simply equate GSS_C_QOP_DEFAULT to a specific explicit QOP
 * value.
 */
#define GSS_C_QOP_DEFAULT 0

/*
 * Expiration time of 2^32-1 seconds means infinite lifetime for a
 * credential or security context
 */
#define GSS_C_INDEFINITE 0xfffffffful


/* Major status codes */

#define GSS_S_COMPLETE 0

/*
 * Some "helper" definitions to make the status code macros obvious.
 */
#define GSS_C_CALLING_ERROR_OFFSET 24
#define GSS_C_ROUTINE_ERROR_OFFSET 16
#define GSS_C_SUPPLEMENTARY_OFFSET 0
#define GSS_C_CALLING_ERROR_MASK 0377ul
#define GSS_C_ROUTINE_ERROR_MASK 0377ul
#define GSS_C_SUPPLEMENTARY_MASK 0177777ul

/*
 * The macros that test status codes for error conditions
 */
#define GSS_CALLING_ERROR(x) \
  (x & (GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET))
#define GSS_ROUTINE_ERROR(x) \
  (x & (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET))
#define GSS_SUPPLEMENTARY_INFO(x) \
  (x & (GSS_C_SUPPLEMENTARY_MASK << GSS_C_SUPPLEMENTARY_OFFSET))
#define GSS_ERROR(x) \
  ((GSS_CALLING_ERROR(x) != 0) || (GSS_ROUTINE_ERROR(x) != 0))


/*
 * Now the actual status code definitions
 */

/*
 * Calling errors:
 */
#define GSS_S_CALL_INACCESSIBLE_READ \
                             (1ul << GSS_C_CALLING_ERROR_OFFSET)
#define GSS_S_CALL_INACCESSIBLE_WRITE \
                             (2ul << GSS_C_CALLING_ERROR_OFFSET)
#define GSS_S_CALL_BAD_STRUCTURE \
                             (3ul << GSS_C_CALLING_ERROR_OFFSET)

/*
 * Routine errors:
 */
#define GSS_S_BAD_MECH (1ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_NAME (2ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_NAMETYPE (3ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_BINDINGS (4ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_STATUS (5ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_SIG (6ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_NO_CRED (7ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_NO_CONTEXT (8ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_DEFECTIVE_TOKEN (9ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_DEFECTIVE_CREDENTIAL (10ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_CREDENTIALS_EXPIRED (11ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_CONTEXT_EXPIRED (12ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_FAILURE (13ul << GSS_C_ROUTINE_ERROR_OFFSET)

/*
 * Supplementary info bits:
 */
#define GSS_S_CONTINUE_NEEDED (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 0))
#define GSS_S_DUPLICATE_TOKEN (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 1))
#define GSS_S_OLD_TOKEN (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 2))
#define GSS_S_UNSEQ_TOKEN (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 3))


/*
 * Finally, function prototypes for the GSSAPI routines.
 */

OM_uint32 gss_acquire_cred
           (OM_uint32*,       /* minor_status */
            gss_name_t,       /* desired_name */
            OM_uint32,        /* time_req */
            gss_OID_set,      /* desired_mechs */
            int,              /* cred_usage */
            gss_cred_id_t*,   /* output_cred_handle */
            gss_OID_set*,     /* actual_mechs */
            OM_uint32*        /* time_rec */
           );

OM_uint32 gss_release_cred
           (OM_uint32*,       /* minor_status */
            gss_cred_id_t*    /* cred_handle */
           );

OM_uint32 gss_init_sec_context
           (OM_uint32*,       /* minor_status */
            gss_cred_id_t,    /* claimant_cred_handle */
            gss_ctx_id_t*,    /* context_handle */
            gss_name_t,       /* target_name */
            gss_OID,          /* mech_type */
            int,              /* req_flags */
            OM_uint32,        /* time_req */
            gss_channel_bindings_t,
                              /* input_chan_bindings */
            gss_buffer_t,     /* input_token */
            gss_OID*,         /* actual_mech_type */
            gss_buffer_t,     /* output_token */
            int*,             /* ret_flags */
            OM_uint32*        /* time_rec */
           );

OM_uint32 gss_accept_sec_context
           (OM_uint32*,       /* minor_status */
            gss_ctx_id_t*,    /* context_handle */
            gss_cred_id_t,    /* verifier_cred_handle */
            gss_buffer_t,     /* input_token_buffer */
            gss_channel_bindings_t,
                              /* input_chan_bindings */
            gss_name_t*,      /* src_name */
            gss_OID*,         /* mech_type */
            gss_buffer_t,     /* output_token */
            int*,             /* ret_flags */
            OM_uint32*,       /* time_rec */
            gss_cred_id_t*    /* delegated_cred_handle */
           );

#if 0	/* not used in this release */
OM_uint32 gss_process_context_token
           (OM_uint32*,       /* minor_status */
            gss_ctx_id_t,     /* context_handle */
            gss_buffer_t      /* token_buffer */
           );
#endif

OM_uint32 gss_delete_sec_context
           (OM_uint32*,       /* minor_status */
            gss_ctx_id_t*,    /* context_handle */
            gss_buffer_t      /* output_token */
           );

#if 0	/* not used in this release */
OM_uint32 gss_context_time
           (OM_uint32*,       /* minor_status */
            gss_ctx_id_t,     /* context_handle */
            OM_uint32*        /* time_rec */
           );
#endif

#if 0	/* not used in this release */
OM_uint32 gss_sign
           (OM_uint32*,       /* minor_status */
            gss_ctx_id_t,     /* context_handle */
            int,              /* qop_req */
            gss_buffer_t,     /* message_buffer */
            gss_buffer_t      /* message_token */
           );
#endif

#if 0	/* not used in this release */
OM_uitn32 gss_verify
           (OM_uint32*,       /* minor_status */
            gss_ctx_id_t,     /* context_handle */
            gss_buffer_t,     /* message_buffer */
            gss_buffer_t,     /* token_buffer */
            int*              /* qop_state */
           );
#endif

#if 0	/* not used in this release */
OM_uint32 gss_seal
           (OM_uint32*,       /* minor_status */
            gss_ctx_id_t,     /* context_handle */
            int,              /* conf_req_flag */
            int,              /* qop_req */
            gss_buffer_t,     /* input_message_buffer */
            int*,             /* conf_state */
            gss_buffer_t      /* output_message_buffer */
           );
#endif

#if 0	/* not used in this release */
OM_uint32 gss_unseal
           (OM_uint32*,       /* minor_status */
            gss_ctx_id_t,     /* context_handle */
            gss_buffer_t,     /* input_message_buffer */
            gss_buffer_t,     /* output_message_buffer */
            int*,             /* conf_state */
            int*              /* qop_state */
           );
#endif

#if 0	/* not used in this release */
OM_uint32 gss_display_status
           (OM_uint32*,       /* minor_status */
            OM_uint32,        /* status_value */
            int,              /* status_type */
            gss_OID,          /* mech_type */
            int*,             /* message_context */
            gss_buffer_t      /* status_string */
           );
#endif

OM_uint32 gss_indicate_mechs
           (OM_uint32*,       /* minor_status */
            gss_OID_set*      /* mech_set */
           );

#if 0	/* not used in this release */
OM_uint32 gss_compare_name
           (OM_uint32*,       /* minor_status */
            gss_name_t,       /* name1 */
            gss_name_t,       /* name2 */
            int*              /* name_equal */
           );
#endif

OM_uint32 gss_display_name
           (OM_uint32*,      /* minor_status */
            gss_name_t,      /* input_name */
            gss_buffer_t,     /* output_name_buffer */
            gss_OID*         /* output_name_type */
           );

OM_uint32 gss_import_name
           (OM_uint32*,       /* minor_status */
            gss_buffer_t,     /* input_name_buffer */
            gss_OID,          /* input_name_type */
            gss_name_t*       /* output_name */
           );

OM_uint32 gss_release_name
           (OM_uint32*,       /* minor_status */
            gss_name_t*       /* input_name */
           );

OM_uint32 gss_release_buffer
           (OM_uint32*,       /* minor_status */
            gss_buffer_t      /* buffer */
           );

#if 0	/* not used in this release */
OM_uint32 gss_release_oid_set
           (OM_uint32*,       /* minor_status */
            gss_OID_set*      /* set */
           );
#endif

#if 0	/* not used in this release */
OM_uint32 gss_inquire_cred
           (OM_uint32 *,      /* minor_status */
            gss_cred_id_t,    /* cred_handle */
            gss_name_t *,     /* name */
            OM_uint32 *,      /* lifetime */
            int *,            /* cred_usage */
            gss_OID_set *     /* mechanisms */
           );
#endif


#endif /* GSSAPI_H_ */

