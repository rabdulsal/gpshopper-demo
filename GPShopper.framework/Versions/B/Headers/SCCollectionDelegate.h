//
//  SCCollectionDelegate.h
//  feature
//
//  Created by kimberly on 8/30/13.
//  Copyright (c) 2013 GPShopper. All rights reserved.
//

#ifndef SCCOLLECTIONDELEGATE_H
#define SCCOLLECTIONDELEGATE_H

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


/**
 Encapsulates the data required to construct a UICollectionViewCell.
 
 Classes that implement SCCollectionEntry *must* implement either:
 
  - nibName
  - cellClass and size

 If nibName is implemented and non-nil, cellClass and size will be ignored.
 
 It is expected that most SCCollectionEntry implementations will use nibName,
 with cellClass being used in a small number of classes requiring greater customization.
 
 ### See also ###
 
 - SCBaseCollectionEntry: the 'standard' implementation of SCCollectionEntry.
   Suggested base class for most use cases.
 - SCSubviewCollectionEntry: the 'view wrapper' implementation of SCCollectionEntry.
 - SCCollectionSupplement
 - SCCollectionSection
 - SCCollectionDelegate
 */
@protocol SCCollectionEntry < NSObject >

@optional
/**
 Nib file used to construct the cell.
 */
-(NSString *)nibName;

/**
 Class used to construct the cell.
 */
-(Class)cellClass;

/**
 Size of cell.  Used only with cellClass.
 */
-(CGSize)size;

/**
 Called when the cell is selected.
 */
-(void)wasSelected;

/**
 Perform additional configuration after a cell is created / dequeued.
 
 Override this method to populate UI elements (set label text, set images, etc.).
 */
-(void)configureCell: (UICollectionViewCell *)c;

@end


/**
 Encapsulates the data required to construct a supplemental view for a UICollectionView.

 Analogous to SCCollectionEntry, much of which applies to this protocol as well.
 
 In particular, classes conforming to this protocol *must* implement one of the following:
 
  - nibName
  - viewClass and size
 
 ### See also ###
 
 - SCBaseCollectionSupplement: the 'standard' implementation of SCCollectionSupplement.
 Suggested base class for most use cases.
 - SCCollectionEntry
 - SCCollectionSection
 - SCCollectionDelegate
 */
@protocol SCCollectionSupplement < NSObject >

@optional

/**
 Nib used to construct the supplemental view.
 */
-(NSString *)nibName;

/**
 Class of the supplemental view contstructed by this object.
 */
-(Class)viewClass;

/**
 Size of the supplemental view.
 */
-(CGSize)size;

/**
 Perform additional configuration after a supplemental view is created / dequeued.
 */
-(void)configureSupplementaryView: (UICollectionReusableView *)v;

@end


/**
 Encapsulates the data required to construct a section inside a UICollectionView.

 ### See also ###
 
 - SCCollectionEntry
 - SCCollectionDelegate
 */
@protocol SCCollectionSection < NSObject >

/**
 SCCollectionEntry instances for the entries in this section.
 */
-(NSArray *)entries;

/**
 Spacing between lines of entries (by default, between rows).
 */
-(CGFloat)minimumLineSpacing;

/**
 Spacing between entries on the same line (by default, on the same row).
 */
-(CGFloat)minimumInteritemSpacing;

/**
 Spacing between entries and the outer bounds of the section.
 */
-(UIEdgeInsets)inset;

/**
 SCCollectionSupplement used to construct the header of this section.
 */
-(id<SCCollectionSupplement>)headerSupplement;

/**
 SCCollectionSupplement used to construct the footer of this section.
 */
-(id<SCCollectionSupplement>)footerSupplement;

@end


/**
 Base implementation of SCCollectionEntry, with settable nibName.
 */
@interface SCBaseCollectionEntry : NSObject < SCCollectionEntry >

@property (copy) NSString *nibName;

@end


/**
 Implementation of SCCollectionEntry intended to wrap UIView
 for display within a UICollectionView.
 */
@interface SCSubviewCollectionEntry : NSObject < SCCollectionEntry >

@property (retain) UIView *view;

@end


/**
 Base implementation of SCCollectionSupplement, with settable nibName;
 */
@interface SCBaseCollectionSupplement : NSObject < SCCollectionSupplement >

@property (copy) NSString *nibName;

@end


/**
 Base implementation of SCCollectionSection, with settable properties.
 */
@interface SCBaseCollectionSection : NSObject < SCCollectionSection >

@property (readonly) NSMutableArray *entries;
@property (readwrite) CGFloat minimumLineSpacing;
@property (readwrite) CGFloat minimumInteritemSpacing;
@property (readwrite) UIEdgeInsets inset;
@property (retain) id<SCCollectionSupplement> headerSupplement;
@property (retain) id<SCCollectionSupplement> footerSupplement;

@end


/**
 Convenience class to ease the use of UICollectionViews.
 
 ### Examples ###
 
 Example 1: checker pattern of two different-sized tiles.
 
     SCBaseCollectionSection *sec=[[SCBaseCollectionSection alloc] init];
     [sec setMinimumInteritemSpacing: 20];
     [sec setMinimumLineSpacing: 20];
     [sec setInset: UIEdgeInsetsMake(10, 10, 10, 10)];
     for (int i=0; i < 64; ++i)
     {
         SCBaseCollectionEntry *e=[[SCBaseCollectionEntry alloc] init];
         [e setNibName: (i % 2 ? @"FDSmallCollectionViewCell" : @"FDMediumCollectionViewCell")];
         [[sec entries] addObject: e];
         [e release];
     }
     [[collectionDelegate sections] addObject: sec];
     [sec release];
 
 
 ### See also ###
 
  - SCCollectionEntry
  - SCCollectionSection
 */
@interface SCCollectionDelegate : NSObject < UICollectionViewDataSource, UICollectionViewDelegate >
{
    NSMutableDictionary *nibSizes;
    NSMutableDictionary *cellDescsToEntries;
}

/**
 SCCollectionSection instances used to populate the view.
 */
@property (readonly) NSMutableArray *sections;

/**
 Looks up the SCCollectionEntry instance used to populate a cell.
 */
-(id<SCCollectionEntry>)entryForCell: (UICollectionViewCell *)c;

@end

#endif
