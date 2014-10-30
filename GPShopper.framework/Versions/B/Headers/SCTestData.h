//
//  SCTestData.h
//  schumacher
//
//  Created by kimberly on 4/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SCTESTDATA_H
#define SCTESTDATA_H


#import <Foundation/Foundation.h>


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@interface NSObject ( GenericMatch )

-(BOOL)consistentWithGenericObject: (NSObject *)generic;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@interface NSString ( GenericMatch )

-(BOOL)consistentWithGenericObject: (NSObject *)generic;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@interface NSNumber ( GenericMatch )

-(BOOL)consistentWithGenericObject:(NSObject *)generic;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@interface NSArray ( GenericMatch )

-(BOOL)consistentWithGenericObject: (NSObject *)generic;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@interface NSDictionary ( GenericMatch )

-(BOOL)consistentWithGenericObject: (NSObject *)generic;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


/**
 Implements a mock version of basic GPShopper mobile api format.
 
 ### About the API ###
 
 In this format, an outgoing communication to the API contains
 one or more **request packets** (usually just one).  These
 are each dictionaries, and together they are sent to the mobile layer
 as a JSON-encoded array.  The following is a typical
 (though pared down) example:
 
     j[{},{"request_type": "search", "query": "hdtv"}]
 
 Note two details:

  * the 'j' prefix: this is an historical artifact to identify
    this request as JSON-formatted.
  * the first dictionary: this is a special **info packet**
    which normally contains additional data like client type id,
    device id, and so on.  SCMockJsonData does not currently
    support any logic based in info packet, and instead
    ignores the first dictionary in any request.
 
 In response, the mobile API returns a JSON-encoded array of dictionaries.
 Here is an example (again, pared down):
 
     [{"products": [], "num_products": 0}]
 
 
 ### Request matching ###
 
 SCMockJsonData maintains a collection of 'template' request packets
 paired with response packets. To mock a response,
 it tries to match the incoming request packet
 with one of its own template packets.
 
 These template request packets may (should) be underspecified
 - they need not contain all the keys / values expected by the mobile API
 for a similar request packet. For example,
 a mock search request packet might specify only request_type
 and query, leaving radius and other keys unspecified.  SCMockJsonData
 matches incoming request packets with the *first non-contradictory*
 request packet on file.

 
 ### File format ###
 
 Mock data is stored in a JSON-formatted file ending in suffix '.mock.json'.
 Each file should contain an array of array of dictionaries:
 
     [
         [ < request dict #1 >, < response dict #1 > ],
         [ < request dict #2 >, < response dict #2 > ],
         ...
         [ < request dict N >, < response dict N > ],
     ]

 For example, a file mocking search data would resemble this
 (some response data removed for brevity):
 
     [
         [
             { "request_type": "search", "query": "hdtv" },
             { "products": [ { "grpid": 12345 } ] }
         ],
         [
             { "request_type": "search", "query": "asdf" },
             { "products": [] }
         ]
     ]
 
 
 ### See also ###
 
 * SCObjectRetriever
 */
@interface SCMockJsonData : NSObject
{
    NSMutableDictionary *responses;
}

/**
 Mimics communication with the remote API.
 
 @param body A fully-formed outgoing message to the API.
 
 @return A fully-formed incoming message as would be received from the API.
 */
-(NSData *)mockResponseForRequestWithBody: (NSString *)body;

-(NSDictionary *)responsePacketMatchingRequestPacket: (NSDictionary *)d;

/**
 Reads request / response packet pairs from a .mock.json file.
 
 @param fn Filename *without* .mock.json suffix (ex "search" for file search.mock.json)
 */
-(void)loadDataFromFile: (NSString *)fn;

+(SCMockJsonData *)defaultData;

@end


@interface SCMockUrlImageData : NSObject
{
    NSMutableDictionary *images;
}

-(UIImage *)imageForUrl: (NSString *)url;

@end

#endif
