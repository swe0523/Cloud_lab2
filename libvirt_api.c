#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{

    int i,val=-1,choice,choice_id,num_domains;
    int *active_domains;
    virConnectPtr conn;
    virDomainPtr vdp_id,vdp_name;
    const char *active_name;
    conn = virConnectOpen("xen:///");
    if (conn == NULL) {
        fprintf(stderr, "Error opening connection to XEN:///  \n");
        return 1;
    }
    else
    {

		    //For finding Active Devices
        num_domains=virConnectNumOfDomains(conn);
        active_domains=malloc(sizeof(int) * num_domains);
        num_domains = virConnectListDomains(conn, active_domains, num_domains);
        free(active_domains);
        for (i = 0 ; i < num_domains ; i++) {
              vdp_id=virDomainLookupByID(conn,i);
              active_name=virDomainGetName(vdp_id);
        }

        while(1)
        {
            printf("1.Start\n2.Suspend\n3.Resume\n4.stop\n5.exit ");
            scanf("%d",&choice);
            if(choice != 5)
            {
                    printf("\nInsert the Active Domian Name");
                    scanf("%s",active_name);
                    vdp_name = virDomainLookupByName(conn,active_name);
            }

            switch(choice)
            {
                case 1:/* Start */
		       val=virDomainCreate(vdp_name);
                       if(val==0)      
                           printf("Success");
                       else
                           printf("Failed");   
                       break;
                case 2:/* Suspend */
		       val=virDomainSuspend(vdp_name);
                       if(val==0)
                           printf("Success");
                       else
                           printf("Failed");   
                       break;
                case 3:/* Resume */ 
		        val=virDomainResume(vdp_name);
                        if(val==0)
                            printf("Success");
                        else
                            printf("Failed");   
                        break;

                case 4: /* stop */
			      val=virDomainShutdown(vdp_name);
                        if(val==0)                     
                            printf("Success");
                        else
                            printf("Failed");   
                        break;
                case 5:  exit(1);
                default:exit(1);
            }
          }
        virConnectClose(conn);
    }
}
